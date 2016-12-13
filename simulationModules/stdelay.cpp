#include "stdelay.h"

STDelay::STDelay(double ts, double delay) : m_ts(ts), m_delay(delay)
{
    int elements = (int)(m_delay / m_ts);
    for (int i = 0; i < elements; i++)
    {
        m_queue.enqueue(SDataVector(0));
    }
}

SDataVector STDelay::execute(SDataVector in)
{
    SDataVector Out;
    m_queue.enqueue(in);
    Out = m_queue.dequeue();
    return Out;
}
