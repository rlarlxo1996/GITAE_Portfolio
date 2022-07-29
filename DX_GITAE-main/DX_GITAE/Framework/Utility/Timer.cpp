#include "framework.h"
#include "Timer.h"

Timer* Timer::_instance = nullptr;
Timer::Timer()
{
	// Update : x������ 1��ŭ�̵�
	// A : 1�ʵ��� 300�� Update -> x : 300 * (�ѹ� ������Ʈ�ϴµ� �ɸ��� �ð� : 1 / 300)
	// B : 1�ʵ��� 100�� Update -> x : 100 * (�ѹ� ������Ʈ�ϴµ� �ɸ��� �ð� : 1 / 100)

	// 1�ʵ��� CPU�� �������� ��ȯ
	QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency);
	// A : 1�ʵ��� 300�� ����
	// B : 1�ʵ��� 100�� ����

	// ���� ������
	QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

	_timeScale = 1.0f / (double)_periodFrequency;

}

Timer::~Timer()
{
}

void Timer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	_deltaTime = (double)(_curTime - _lastTime) * _timeScale;
	if (_lockFPS != 0)
	{
		while (_deltaTime < (1.0 / _lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			// �� �� �����Ӹ�ŭ ����� �ð�
			_deltaTime = (double)(_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;

	_frameCount++;
	_oneSecCount += _deltaTime;

	// 1�ʸ��� �����ؾߵǴ� ����
	if (_oneSecCount >= 1)
	{
		_oneSecCount = 0;
		_frameRate = _frameCount;
		// frameRate == FPS
		// FPS : Frame Per Second;
		_frameCount = 0;
	}

	_runTime += _deltaTime;
}
