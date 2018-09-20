#ifndef _DClock_h
#define _DClock_h

using namespace std;

class DClock {
	private:
		int hours, minutes;
		bool apm;

	public:
		DClock();
		DClock(int hour, int minute);
		
		int get_hours();
		int get_minutes();
		int get_ampm();
		
		void increment();
};

#endif
