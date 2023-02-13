/* @author AOL
 * @brief Adds /tps, which displays TPS info. Some code is based off of a plugin by jdb.
*/
#include "../inc/util.hpp"

#define DIGIT_PRECISION 2
#define TICKS_PER_UPDATE 125
#define SECONDS_PER_MINUTE 60
#define SECONDS_PER_HALF_HOUR SECONDS_PER_MINUTE * 30
#define SECONDS_PER_HOUR SECONDS_PER_MINUTE * 60
#define NO_VALUE -1

static double lastCalcTime = getEpochTime();
static char secondTickCount = 0;

static double fiveSecTPS[5];
static double minuteTPS[SECONDS_PER_MINUTE];
static double halfHourTPS[SECONDS_PER_HALF_HOUR];
static double hourTPS[SECONDS_PER_HOUR];

static unsigned short fiveSecIndex = 0;
static unsigned short minuteIndex = 0;
static unsigned short halfHourIndex = 0;
static unsigned short hourIndex = 0;

static std::string averageToString(double* array, unsigned short size)
{
    long double sum = 0;
    unsigned short i = -1;
    while (++i < size && array[i] != NO_VALUE)
        sum += array[i];
    if (i == 0) return "0.00";

    // Gets the average (sum / --i)
    // Shifts the decimal place left (* pow(10, DIGIT_PRECISION))
    // Rounds to nearest integer (int)(+ 0.5)
    // Casts to float
    // Shifts decimal place right (* pow(10, -DIGIT_PRECISION))
    std::string res = std::to_string((float)((int)((sum / --i) * 
                      pow(10, DIGIT_PRECISION) + 0.5)) * pow(10, -DIGIT_PRECISION));
    std::size_t cutPos = res.find('.');
    if (cutPos == std::string::npos) return res;
    cutPos += DIGIT_PRECISION + 1;
    if (cutPos >= res.length()) return res;
    return res.substr(0, cutPos);
}

static HookOnce LogicInit(
    &Logic,
    []()
    {
        for (double& tickCount : fiveSecTPS)
            tickCount = NO_VALUE;
        for (double& tickCount : minuteTPS)
            tickCount = NO_VALUE;
        for (double& tickCount : halfHourTPS)
            tickCount = NO_VALUE;
        for (double& tickCount : hourTPS)
            tickCount = NO_VALUE;
        return HOOK_CONTINUE;
    },
    -1
);

static Hook LogicHook(
    &Logic,
    []()
    {
        if (++secondTickCount == TICKS_PER_UPDATE)
        {
            secondTickCount = 0;

            double curTime = getEpochTime();
            double tps = TICKS_PER_UPDATE / (curTime - lastCalcTime);
            lastCalcTime = curTime;

            fiveSecTPS[fiveSecIndex] = tps;
            minuteTPS[minuteIndex] = tps;
            halfHourTPS[halfHourIndex] = tps;
            hourTPS[hourIndex] = tps;

            if (++fiveSecIndex >= 5) fiveSecIndex = 0;
            if (++minuteIndex >= SECONDS_PER_MINUTE) minuteIndex = 0;
            if (++halfHourIndex >= SECONDS_PER_HALF_HOUR) halfHourIndex = 0;
            if (++hourIndex >= SECONDS_PER_HOUR) hourIndex = 0;
        }
        return HOOK_CONTINUE;
    }
);

Command tps(
    "/tps",
    [](Player* player, std::vector<std::string> args)
    {
        player->sendMessage(format("TPS last 5s, 1m, 30m, 1h: {} {} {} {}",
                            averageToString(fiveSecTPS, 5), averageToString(minuteTPS, SECONDS_PER_MINUTE),
                            averageToString(halfHourTPS, SECONDS_PER_HALF_HOUR), averageToString(hourTPS, SECONDS_PER_HOUR)));
    }
);
