#ifndef DESERIAL_H
#define DESERIAL_H

#include <iostream>

struct T_DSEQ
{
    std::string dState_INPUT = "";
    std::string dState_PROCESSING = "";
    std::string dState_OUTPUT = "";
};

/* dstate */
#define DSTATE_SERIALIZE_START '('
#define DSTATE_SERIALIZE_DELIMITER ';'
#define DSTATE_SERIALIZE_END ')'

/* dSeq */
#define DSEQ_SERIALIZE_DELIMITER ','

std::ostream &operator<<(std::ostream &out, const T_DSEQ &transmit)
{
    out << DSTATE_SERIALIZE_START << transmit.dState_INPUT << DSTATE_SERIALIZE_END
        << DSEQ_SERIALIZE_DELIMITER << transmit.dState_PROCESSING << DSEQ_SERIALIZE_DELIMITER
        << DSTATE_SERIALIZE_START << transmit.dState_OUTPUT << DSTATE_SERIALIZE_END;
    return out;
}

std::istream &operator>>(std::istream &in, T_DSEQ &transmit)
{
    //wahrscheinlich wurde schon etwas aus in weggenommen. vorher "token"
    char singlechar;
   char start, end, delimiter;

   /// Eingabe dState lesen
    in >> start;
    if (start == DSTATE_SERIALIZE_START)
    {
        std::getline(in, transmit.dState_INPUT, DSTATE_SERIALIZE_END);
        in >> delimiter; // Sollte das Trennzeichen ',' sein
    }
    std::getline(in, transmit.dState_PROCESSING, DSEQ_SERIALIZE_DELIMITER);

    // Ausgabe dState lesen
    in >> start;
    if (start == DSTATE_SERIALIZE_START)
    {
        std::getline(in, transmit.dState_OUTPUT, DSTATE_SERIALIZE_END);
    }

/*
    in >> singlechar;
    if (singlechar == DSTATE_SERIALIZE_START)
    {
        in >> transmit.dState_INPUT;
        in >> singlechar;
        if (singlechar == DSTATE_SERIALIZE_END)
        {
            in >> singlechar;
            if (singlechar != DSEQ_SERIALIZE_DELIMITER)
            {
                in >> transmit.dState_PROCESSING;
                in >> singlechar;
                if (singlechar != DSEQ_SERIALIZE_DELIMITER)
                {
                    in >> singlechar;
                    if (singlechar != DSTATE_SERIALIZE_START)
                    {
                        in >> transmit.dState_OUTPUT;
                        in >> singlechar;
                        if (singlechar == DSTATE_SERIALIZE_END)
                        {
                            // deserializationAssert();
                            // in.clear();
                        }
                    }
                }
            }
        }
    }
    */
    return in;
}

#endif