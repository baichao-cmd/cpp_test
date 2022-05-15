#include <iostream>
#include <string.h>
#include <mutex>

#define LL_ADD(item, list)                      \
	do                                          \
	{                                           \
		item->prev = NULL;                      \
		item->next = list;                      \
		if (list != NULL && list->prev != NULL) \
			list->prev = item;                  \
		list = item;                            \
	} while (0)

#define LL_REMOVE(item, list)              \
	do                                     \
	{                                      \
		if (item->prev != NULL)            \
			item->prev->next = item->next; \
		if (item->next != NULL)            \
			item->next->prev = item->prev; \
		if (list == item)                  \
			list = item->next;             \
		item->prev = item->next = NULL;    \
	} while (0)

typedef struct NWORKER
{
	pthread_t threadid; // 线程ID
	int terminate;		// 放缩系数,控制"活"线程数量

	struct THREADPOOL *pool;

	struct NWORKER *prev;
	struct NWORKER *next;
} NWORKER;

// 任务队列
typedef struct NJOB
{
	void (*job_function)(struct NJOB *job);
	void *user_data;
	struct NJOB *prev;
	struct NJOB *next;
} NJOB;

typedef struct THREADPOOL
{

	struct NWORKER *workers;
	struct NJOB *waiting_jobs;
	pthread_mutex_t jobs_mtx;
	pthread_cond_t jobs_cond;
} THREADPOOL;

void *ThreadCallback(void *arg)
{
	NWORKER *worker = (NWORKER *)arg;
	while (1)
	{
		pthread_mutex_lock(&worker->pool->jobs_mtx);
		while (worker->pool->waiting_jobs == NULL)
		{
			if (worker->terminate)
			{
				break;
			}
			/*
			   pthread_cond_wait开始前需要mutex来保护cond,但是在阻塞等待时会释放锁,因为锁被释放了cond才能在其他地方被改变,满足当前等待条件.被唤醒后返回时又会给cond继续加上锁.
			   */
			pthread_cond_wait(&worker->pool->jobs_cond, &worker->pool->jobs_mtx);
		}

		if (worker->terminate)
		{
			pthread_mutex_unlock(&worker->pool->jobs_mtx);
			break;
		}

		NJOB *job = worker->pool->waiting_jobs;
		if (job != NULL)
		{
			LL_REMOVE(job, worker->pool->waiting_jobs);
		}
		pthread_mutex_unlock(&worker->pool->jobs_mtx);

		// if (job == NULL)
		// {
		//     continue;
		// }

		job->job_function(job);
	}

	free(worker);
	pthread_exit(NULL);
	return NULL;
}

// api
int ThreadPoolCreate(THREADPOOL *workqueue, int numWorkers)
{
	// 检测参数
	if (numWorkers < 1)
		numWorkers = 1;
	memset(workqueue, 0, sizeof(THREADPOOL));

	// 初始化条件变量
	pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
	memcpy(&workqueue->jobs_cond, &blank_cond, sizeof(pthread_cond_t));

	// 初始化互斥锁
	pthread_mutex_t blank_mutex = PTHREAD_MUTEX_INITIALIZER;
	memcpy(&workqueue->jobs_mtx, &blank_mutex, sizeof(pthread_mutex_t));

	// 创建worker
	int i = 0;
	for (i = 0; i < numWorkers; ++i)
	{
		NWORKER *worker = (NWORKER *)malloc(sizeof(NWORKER));
		if (worker == NULL)
		{
			perror("malloc");
			return 1;
		}
		memset(worker, 0, sizeof(NWORKER));
		worker->pool = workqueue;
		int ret = pthread_create(&worker->threadid, NULL, ThreadCallback, (void *)worker);
		if (ret)
		{
			perror("pthread_create");
			free(worker);
		}
		LL_ADD(worker, worker->pool->workers);
	}
	return 0;
}

int ThreadPoolPushTask(THREADPOOL *pool, NJOB *job)
{
	pthread_mutex_lock(&pool->jobs_mtx);
	LL_ADD(job, pool->waiting_jobs);
	pthread_cond_signal(&pool->jobs_cond);
	pthread_mutex_unlock(&pool->jobs_mtx);
	return 0;
}

void ThreadPoolShutdown(THREADPOOL *pool)
{
	NWORKER *worker = NULL;
	for (worker = pool->workers; worker != NULL; worker = worker->next)
	{
		worker->terminate = 1;
	}
	pthread_mutex_lock(&pool->jobs_mtx);

	pool->workers = NULL;
	pool->waiting_jobs = NULL;

	pthread_cond_broadcast(&pool->jobs_cond);
	pthread_mutex_unlock(&pool->jobs_mtx);
}

#if 1

//最大线程数量
#define MAX_THREAD_NUM 4
#define HANDLER_MAX_NUM 1000

void Counter(NJOB *job)
{
	int index = *(int *)job->user_data;

	printf("index:%d,selfid:%lu\n", index, pthread_self());

	free(job->user_data);
	free(job);
}

int main()
{
	THREADPOOL pool;
	ThreadPoolCreate(&pool, MAX_THREAD_NUM);

	for (int i = 0; i < HANDLER_MAX_NUM; ++i)
	{
		NJOB *job = (NJOB *)malloc(sizeof(NJOB));
		if (job == NULL)
		{
			perror("malloc");
			exit(1);
		}

		job->job_function = Counter;
		job->user_data = malloc(sizeof(int));
		*(int *)job->user_data = i;

		ThreadPoolPushTask(&pool, job);
	}

	getchar();
	printf("\n");
	return 0;
}

#endif
