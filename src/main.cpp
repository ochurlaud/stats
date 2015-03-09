#include <fstream>
#include <ctime>
#include <linux/input.h>
#include <vector>

#define EV_PRESSED 1
#define EV_RELEASED 0
#define EV_REPEAT 2

int main()
{
    time_t originTime = time(NULL);
    struct input_event event;
    unsigned int scan_code = 0;
    std::vector<int> charVect(255);
    double lastTimeDouble(0);
    double timeDouble(0);
    double minTime(1000);
    
    std::ifstream dev2("/dev/input/event0");
    if(dev2.is_open())
    {
	int i = 0;
        while(dev2.read((char*)&event, sizeof(input_event)))
        {
            if(event.value==EV_PRESSED)
            {
                scan_code = event.code;
                charVect[scan_code]++;
		timeDouble = event.time.tv_sec + event.time.tv_usec /1000000.0; 
		if ((timeDouble - lastTimeDouble) < minTime)
		{
		    minTime = timeDouble - lastTimeDouble;
		}
		lastTimeDouble = timeDouble;
		i++;
            }
            if(i == 100)
	    {
		int sum(0);
		for (int j = 0 ; j < charVect.size() ; j++)
		{
		    printf("[%u] = %u\n", j, charVect[j]);
		    sum = sum+charVect[j];
		}
		printf("\n");
		printf("t_min = %fs\n",minTime);
		double average = sum/difftime(time(NULL), originTime);
		printf("average = %f key/s\n======\n", average);
		i = 0;
	    }
        }
        dev2.close();
    }
    else
    {
        return -1;
    }
    return 0;
}
