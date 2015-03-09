/*
 * shm_com.h
 *
 *  Created on: Mar 10, 2015
 *      Author: shane
 */

#ifndef SHM_COM_H_
#define SHM_COM_H_

#define TEXT_SIZE 2018  // 共享内存size
struct shared_use_st{
	int written_by_you;
	char some_text[TEXT_SIZE];
};

#endif /* SHM_COM_H_ */
