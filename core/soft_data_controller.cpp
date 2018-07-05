#include "stdafx.h"
#include "soft_data_controller.h"
// #include "base/logging.h"
// #include "base/thread_task_runner_handle.h"
// #include "base/bind.h"
//#include "base/bind_helpers.h"
//#include "base/file_util.h"
//#include "base/location.h"
//#include "base/message_loop/message_loop_proxy.h"
//#include "base/task_runner.h"
//#include "base/task_runner_util.h"
#include "load_soft_data_task.h"
//#include "../utils/http_client.h"

SoftDataController::SoftDataController()/*:task_runner_(nullptr)*/{
// 	task_runner_thread_.reset(new base::Thread("SoftDataController"));
// 	task_runner_thread_->Start();
// 	task_runner_ = task_runner_thread_->message_loop_proxy().get();
// 
// 	//
// 	http_client_.reset(new HttpClient);
//	http_client_->set_timeout(30);
}

void SoftDataController::RunGetSoftList(){
	LoadSoftDataRuner* helper = new LoadSoftDataRuner();

	//base::FilePath file_path;
	//task_runner_->PostTaskAndReply(FROM_HERE,
	//	base::Bind(&LoadSoftDataRuner::RunWorkForFilePath,
	//		base::Unretained(helper), file_path),
	//	base::Bind(&LoadSoftDataRuner::Reply, base::Owned(helper)));
}
//
//bool SoftDataController::PostTask(
//	const tracked_objects::Location& from_here,
//	const base::Closure& task) {
//	return task_runner_->PostTask(from_here, task);
//}
SoftDataController::~SoftDataController(){
}
