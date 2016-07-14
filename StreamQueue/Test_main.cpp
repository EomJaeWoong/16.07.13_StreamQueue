#include "StreamQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

CAyaStreamSQ StreamQ(200);

void main()
{
	char* str = { "Better late than naver. make today the best day of your life" };
	char *Input = NULL;
	char *output = NULL;
	int PrevIndexInput = 0;
	int InputRandom;
	int OutputRandom;

	StreamQ.ClearBuffer();

	while(1)
	{
		int retval;

		srand(time(NULL));
		////////////////////////////////////////////////////
		InputRandom = (rand() % 30) + 1;
		Input = new char[InputRandom];

		for (int iCnt = 0; iCnt < InputRandom; iCnt++)
		{
			Input[iCnt] = str[PrevIndexInput++];
			if (PrevIndexInput >= strlen(str))	PrevIndexInput -= strlen(str);
		}
		////////////////////////////////////////////////////
		retval = StreamQ.Put(Input, InputRandom);
		if (InputRandom != retval)
		{
			PrevIndexInput -= InputRandom - retval;
			if (PrevIndexInput < 0)	PrevIndexInput += strlen(str);
		}


		////////////////////////////////////////////////////
		OutputRandom = (rand() % 30) + 1;
		output = new char[OutputRandom + 1];
		////////////////////////////////////////////////////
		
		retval = StreamQ.Get(output, OutputRandom);

		output[retval] = '\0';

		printf("%s", output);

		delete[] Input;
		delete[] output;
		Sleep(80);
	}
}