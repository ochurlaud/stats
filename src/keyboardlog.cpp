/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "keyboardlog.h"

KeyboardLog::KeyboardLog():
     m_inputFile("/dev/input/event0")
    ,m_charVect(255)
{
    m_minTime.tv_sec=200;
    m_originTime = time(NULL);
    m_inputStream = new std::ifstream;
}

KeyboardLog::~KeyboardLog()
{
    delete m_inputStream;
}

void KeyboardLog::start()
{
    m_thread = std::thread(&KeyboardLog::run, this) ;
}

void KeyboardLog::join()
{
    m_thread.join();
}

int KeyboardLog::run()
{
    m_inputStream->open(m_inputFile.c_str());
    
    if (!m_inputStream->is_open()) {
	return -1;
    }
    
    struct input_event event;
    int i = 0;
    double lastTimeDouble(0);
    double timeDouble(0);
    struct timeval lastTime;
    lastTime.tv_sec = 0;
    lastTime.tv_usec = 0;
    
    while(m_inputStream->read((char*)&event, sizeof(input_event))) {
	if(event.value == EV_PRESSED)
	{
	    m_charVect[event.code]++;
	    struct timeval diffTime;
	    timersub(&(event.time), &lastTime, &diffTime);
	    if (timercmp(&diffTime, &m_minTime, <)) {
		m_minTime = diffTime;
	    }
	    lastTime = event.time;
	    i++;
	}
	if(i == 10)
	{
	    int sum(0);
	    for (int j = 0 ; j < m_charVect.size() ; j++)
	    {
		printf("[%u] = %u\n", j, m_charVect[j]);
		sum = sum+m_charVect[j];
	    }
	    printf("\n");
	    printf("t_min = %2ld.%05lds\n",m_minTime);
	    double average = sum/difftime(time(NULL), m_originTime);
	    printf("average = %f key/s\n======\n", average);
	    /*statsfile.open(statsfilePath.c_str());
	    statsfile << "[t_orig]\t" << m_originTime << std::endl;
	    statsfile << "[t_min]\t\t" << m_minTime / 1000000.0<< std::endl;
	    statsfile << "[average]\t" << average << std::endl;
	    statsfile.close();*/
	    
	    i = 0;
	}
    }
    m_inputStream->close();
    return 0;
}