/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef TASKMANAGERIMPL_H_
#define TASKMANAGERIMPL_H_

#include "system/lang.h"

#include "engine/log/Logger.h"

//#include "engine/util/Singleton.h"

#include "TaskManager.h"

#include "TaskQueue.h"

namespace engine {
  namespace core {

	class TaskWorkerThread;
	class TaskScheduler;
	class Task;

	class TaskManagerImpl : public TaskManager, /*public Singleton<TaskManagerImpl>,*/ public Mutex, public Logger {
		TaskQueue tasks;

		Vector<TaskWorkerThread*> workers;
		Vector<TaskScheduler*> schedulers;

		int workerThreads;
		int schedulerThreads;

		int currentTaskScheduler;

		bool shuttingDown;

  		SortedVector<Task*> cancelledTasks;

		static const int DEAFULT_WORKER_THREADS = 1;
		static const int DEAFULT_SCHEDULER_THREADS = 1;

	public:
		TaskManagerImpl();

		virtual ~TaskManagerImpl();

		void initialize();

		void initialize(int workerCount, int schedulerCount);

		void start();

		void shutdown();

		void executeTask(Task* task);

		void scheduleTask(Task* task, uint64 delay = 0);
		void scheduleTask(Task* task, Time& time);

		void rescheduleTask(Task* task, uint64 delay = 0);
		void rescheduleTask(Task* task, Time& time);

		bool cancelTask(Task* task);

		void flushTasks();

		void clearTasks();

		void testScheduler();

		void printInfo();

		int getScheduledTaskSize();

		int getExecutingTaskSize();

	private:
		void mergeTasks(TaskManagerImpl* manager);

		TaskScheduler* getTaskScheduler();

		void setTaskScheduler(Task* task, TaskScheduler* scheduler);

		bool isRunning() {
			// FIXME - hack
			return !workers.isEmpty();
		}

		inline Task* getTask() {
			return tasks.pop();
		}

		friend class TaskScheduler;
		friend class TaskWorkerThread;
		friend class TransactionalTaskManager;
	};

  } // namespace core
} // namespace engine

using namespace engine::core;

#endif /* TASKMANAGERIMPL_H_ */