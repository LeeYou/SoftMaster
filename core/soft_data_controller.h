
#ifndef SOFT_DATA_CONTROLLER_H_
#define SOFT_DATA_CONTROLLER_H_

//#include "base/basictypes.h"
//#include "base/compiler_specific.h"
//#include "base/single_thread_task_runner.h"
//#include "base/threading/thread_checker.h"
//#include "base/compiler_specific.h"
//#include "base/logging.h"
//#include "base/threading/post_task_and_reply_impl.h"
//#include "base/threading/thread.h"
#include <deque>


namespace base{
	class TimeDelta;
}
class HttpClient;

class SoftDataController 
	/*:public base::internal::PostTaskAndReplyImpl*/ {
public:
	explicit SoftDataController();
	virtual ~SoftDataController();
	void RunGetSoftList();
protected:
	//virtual bool PostTask(const tracked_objects::Location& from_here,
	//	const base::Closure& task) OVERRIDE;

private:
	DISALLOW_COPY_AND_ASSIGN(SoftDataController);
// 	base::TaskRunner* task_runner_;
// 	scoped_ptr<base::Thread> task_runner_thread_;
// 	scoped_ptr<HttpClient> http_client_;
};

#endif
