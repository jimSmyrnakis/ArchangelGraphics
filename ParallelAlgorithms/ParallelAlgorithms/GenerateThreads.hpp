#pragma once
#include <windows.h>
#include <vector>
typedef void (*ThreadFunction)(void*);

class ThreadsGenerator {

private:
	int m_numThreads;
	ThreadFunction m_function;
	HANDLE* m_threads;

};