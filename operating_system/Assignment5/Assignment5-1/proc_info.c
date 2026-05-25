#include <linux/module.h>
#include <linux/pid.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/uidgid.h>

#define PROC_DIR_NAME "proc_2020202090"
#define PROC_FILE_NAME "processInfo"

static struct proc_dir_entry *proc_dir;
static struct proc_dir_entry *proc_file;
static int target_pid = -1;
static char *proc_buffer;
static size_t proc_buffer_size;

// convert task state to a string
static const char *get_task_state(long state)
{
    switch (state)
    {
    case TASK_RUNNING:
        return "R (running)";
    case TASK_INTERRUPTIBLE:
        return "S (sleeping)";
    case TASK_UNINTERRUPTIBLE:
        return "D (disk sleep)";
    case __TASK_STOPPED:
        return "T (stopped)";
    case __TASK_TRACED:
        return "t (tracing stop)";
    case EXIT_DEAD:
        return "X (dead)";
    case TASK_DEAD:
        return "Z (zombie)";
    case TASK_PARKED:
        return "P (parked)";
    case TASK_IDLE:
        return "I (idle)";
    default:
        return "? (unknown)";
    }
}

// write process information to the buffer
static void write_process_info(struct task_struct *task, char **buffer_ptr, size_t *remaining_size)
{
    struct user_namespace *user_ns = current_user_ns();
    int len;

    len = snprintf(*buffer_ptr, *remaining_size, "%-8d %-8d %-8u %-8u %-10lu %-10lu %-8s %-s\n", task->pid,
                   task->real_parent->pid, from_kuid(user_ns, task->cred->uid), from_kgid(user_ns, task->cred->gid),
                   task->utime, task->stime, get_task_state(task->state), task->comm);

    if (len > 0 && len < *remaining_size)
    {
        *buffer_ptr += len;
        *remaining_size -= len;
    }
}

// write header and all processes' information to the buffer
static void write_all_processes_info(char *buffer, size_t buffer_size)
{
    struct task_struct *task;
    char *buffer_ptr = buffer;
    int len;

    // write header to the buffer
    len = snprintf(buffer_ptr, buffer_size,
                   "PID      PPID     UID      GID      UTIME      STIME      STATE    "
                   "NAME\n----------------------------------------------------------------------------\n");
    buffer_ptr += len;
    buffer_size -= len;

    for_each_process(task)
    {
        write_process_info(task, &buffer_ptr, &buffer_size);

        if (buffer_size <= 0)
            break;
    }
}

// read operation
static ssize_t proc_read(struct file *file, char __user *user_buffer, size_t count, loff_t *offset)
{
    struct task_struct *task;

    if (*offset > 0)
        return 0;

    // allocate the buffer dynamically if not already allocated
    if (!proc_buffer)
    {
        proc_buffer_size = PAGE_SIZE * 4; // 16 KB buffer
        proc_buffer = kmalloc(proc_buffer_size, GFP_KERNEL);
        if (!proc_buffer)
            return -1;
    }

    // prepare the process information for reading
    if (target_pid == -1)
    {
        write_all_processes_info(proc_buffer, proc_buffer_size);
    }
    else
    {
        char *buffer_ptr = proc_buffer;
        size_t buffer_size = proc_buffer_size;

        rcu_read_lock();
        task = pid_task(find_vpid(target_pid), PIDTYPE_PID);

        if (task)
        {
            int len;
            // write header to the buffer
            len = snprintf(buffer_ptr, buffer_size,
                           "PID      PPID     UID      GID      UTIME      STIME      STATE    "
                           "NAME\n----------------------------------------------------------------------------\n");
            buffer_ptr += len;
            buffer_size -= len;
            write_process_info(task, &buffer_ptr, &buffer_size);
        }
        else
        {
            snprintf(proc_buffer, proc_buffer_size, "No such process with PID: %d\n", target_pid);
        }

        rcu_read_unlock();
    }

    // copy buffer content to user space
    return simple_read_from_buffer(user_buffer, count, offset, proc_buffer, strlen(proc_buffer));
}

// write operation
static ssize_t proc_write(struct file *file, const char __user *user_buffer, size_t count, loff_t *offset)
{
    char buffer[16];
    long pid;
    int ret;

    if (count > sizeof(buffer) - 1)
        return -1;

    if (copy_from_user(buffer, user_buffer, count))
        return -1;

    // set termination
    buffer[count] = '\0';

    ret = kstrtol(buffer, 10, &pid);

    if (ret)
        return ret;

    target_pid = (pid >= 0) ? pid : -1;

    return count;
}

// file operations
static const struct file_operations proc_fops = {
    .owner = THIS_MODULE,
    .read = proc_read,
    .write = proc_write,
};

// module initialization
static int __init proc_info_init(void)
{
    // create /proc/proc_2020202090
    proc_dir = proc_mkdir(PROC_DIR_NAME, NULL);

    if (!proc_dir)
        return -1;

    // create processInfo
    proc_file = proc_create(PROC_FILE_NAME, 0666, proc_dir, &proc_fops);

    if (!proc_file)
    {
        remove_proc_entry(PROC_DIR_NAME, NULL);
        return -1;
    }

    proc_buffer = NULL;
    proc_buffer_size = 0;

    printk(KERN_INFO "Module loaded: %s/%s\n", PROC_DIR_NAME, PROC_FILE_NAME);
    return 0;
}

// module cleanup
static void __exit proc_info_exit(void)
{
    if (proc_buffer)
        kfree(proc_buffer);

    remove_proc_entry(PROC_FILE_NAME, proc_dir);
    remove_proc_entry(PROC_DIR_NAME, NULL);
    printk(KERN_INFO "Module unloaded: %s/%s\n", PROC_DIR_NAME, PROC_FILE_NAME);
}

module_init(proc_info_init);
module_exit(proc_info_exit);
MODULE_LICENSE("GPL");
