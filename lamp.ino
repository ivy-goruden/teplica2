void lamp_func()
{
    if (lamp_sost = LOW) lamp_sost = HIGH;
    if (lamp_sost = HIGH)lamp_sost = LOW;
    digitalWrite(lamp, lamp_sost);
}