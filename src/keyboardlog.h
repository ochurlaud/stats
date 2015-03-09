/*
 * stats does stats on your behavior, but stays on your computer
 * Copyright (C) 2015  Olivier CHURLAUD <olivier@churlaud.com>
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

#ifndef KEYBOARDLOG_H
#define KEYBOARDLOG_H

#include <linux/input.h>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <thread>


#define EV_PRESSED 1
#define EV_RELEASED 0
#define EV_REPEAT 2

class KeyboardLog
{
public:
    KeyboardLog();
    ~KeyboardLog();
    int run();
    void start();
    void join();
    
private:
    std::vector<int> m_charVect;
    std::string m_inputFile;
    std::ifstream *m_inputStream;
    struct timeval m_minTime;
    double m_minTime10;
    
    time_t m_originTime;
    std::thread m_thread;
};

#endif // KEYBOARDLOG_H
