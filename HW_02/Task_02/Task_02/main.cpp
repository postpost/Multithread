#include <iostream>
#include <thread>
#include <Windows.h>
#include <chrono>
#include <mutex>
#include <vector>
#include "timer.h"

using namespace std::chrono_literals;
std::mutex m;
std::atomic_flag flag = ATOMIC_FLAG_INIT;
std::condition_variable data_cond;
std::once_flag once;
bool notify{ false };

void print_headers() {
	std::cout << "Id\t\tProgress Bar\t\tTime\n\n";
}

void DrawProgressBar() {
	system("color 0A");
	//initialize char to print bar
	//char a = 176, b = 219; //221
	for (int i = 0; i < 10; ++i) {
		std::cout << i;
		Sleep(500);
	}
}
void LoadBar(int i) {
	//���� ������� ����� ��� 4 ������
	std::call_once(once, print_headers);
	Timer timer;
	std::unique_lock lk(m);
	std::cout << std::this_thread::get_id() << "\n";
	lk.unlock();
	timer.start();
	//...to do

	DrawProgressBar();
	timer.print();
}

void task() {
	std::vector < std::thread> vt;
	for (int i = 0; i < 4; ++i) {
		vt.push_back(std::thread(LoadBar, i));
	}
	for (auto& el:vt) {
		el.join();
	}
}


int main_01() {
	task();
	return 0;
}