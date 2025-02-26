﻿#include <iostream>

struct Time {
    short hours;
    short minutes;
    short seconds;

    void addSeconds(short count) {
        seconds += count;
        if (seconds >= 60) {
            count = seconds / 60;
            seconds %= 60;
        }
        else return;

        minutes += count;
        if (minutes >= 60) {
            count = minutes / 60;
            minutes %= 60;
        }
        else return;

        hours += count;
        if (hours >= 60)
            hours = minutes = seconds = 0;
    }
};

bool operator==(const Time& lhs, const Time& rhs) {
    return lhs.hours == rhs.hours &&
        lhs.minutes == rhs.minutes &&
        lhs.seconds == rhs.seconds;
}

bool operator!=(const Time& lhs, const Time& rhs) {
    return not (lhs == rhs);
}

bool operator<(const Time& lhs, const Time& rhs) {
    return lhs.hours * 3600 + lhs.hours * 60 + lhs.seconds < rhs.hours * 3600 + rhs.hours * 60 + rhs.seconds;
}

class IRunnable {
public:
    virtual void run() = 0;
};

class IClock {
public:
    virtual void add(IRunnable* client, Time time) = 0;
    virtual bool next() = 0;
};

class Clock : public IClock, public IRunnable {
    //short a;
    //short b;
   // short c;
public:
    void add(IRunnable* client, Time time) override {
        std::cout << (time.hours >= 10 ? "" : "0") << time.hours << (time.minutes >= 10 ? ":" : ":0") << time.minutes << (time.seconds >= 10 ? ":" : ":0") << time.seconds << " ";
        client->run();

    }
    bool next() override {
        return true;
    }
    void run() override {

    }
};

class OSUpdater : public IRunnable {
    void run() override {
        std::cout << "OSUpdater" << std::endl;
    }
};

class Alarm : public IRunnable {
    void run() override {
        std::cout << "Alarm" << std::endl;
    }
};

class ActivityChecker : public IRunnable {
public:
    void run() override {
        std::cout << "ActivityChecker" << std::endl;
    }
};

// Ваш код здесь

int main() {
    int monentum;
    std::cin >> monentum;
    srand(monentum);  // Фиксируем случайность

    IClock* clock = new Clock;
    IRunnable* timer = (Clock*)clock;

    Time t = { 0, 0, 0 }, midnight = { 0, 0, 0 };

    do {
        int type = rand() % 3;
        if (type == 0) clock->add(new OSUpdater, t);
        else if (type == 1) clock->add(new Alarm, t);
        else if (type == 2) clock->add(new ActivityChecker, t);
        t.addSeconds(3600 + rand() % 3600);
    } while (t != midnight);

    timer->run();
}