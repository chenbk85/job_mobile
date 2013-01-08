/* file : MSG_presence_task.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2013-01-08 11:41:47
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __MSG_presence_task_header__
#define __MSG_presence_task_header__
#pragma once

class MSG_presence_Task: public Poco::Task
{
public:
  MSG_presence_Task(): Poco::Task("MSG_presence_Task")
  {
  }
  void runTask();

};

#endif // __MSG_presence_task_header__
