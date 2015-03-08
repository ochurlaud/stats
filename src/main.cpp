#include <fstream>
#include <linux/input.h>

#define EV_PRESSED 1
#define EV_RELEASED 0
#define EV_REPEAT 2

int main()
{
    struct input_event event;
    unsigned int scan_code = 0;

    std::ifstream dev2("/dev/input/event0");
    if(dev2.is_open())
    {
        while(dev2.read((char*)&event, sizeof(input_event)))
        {
            if(event.value==EV_PRESSED)
            {
                scan_code = event.code;
                printf("%u\n",scan_code);
                printf("%ld.%06ld\n",event.time.tv_sec,event.time.tv_usec);
                printf("\n");
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
