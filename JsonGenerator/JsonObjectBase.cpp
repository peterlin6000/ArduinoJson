/*
* Arduino JSON library
* Benoit Blanchon 2014 - MIT License
*/

#include "JsonObjectBase.h"
#include <string.h> // for strcmp

using namespace ArduinoJson::Generator;
using namespace ArduinoJson::Internals;

size_t JsonObjectBase::printTo(Print& p) const
{
    size_t n = 0;

    n += p.write('{');

    // NB: the code has been optimized for a small size on a 8-bit AVR

    const KeyValuePair* current = items;
    for (int i = count; i > 0; i--)
    {       
        n += EscapedString::printTo(current->key, p);
        n += p.write(':');
        n += current->value.printTo(p);

        current++;

        if (i > 1)
        {
            n += p.write(',');
        }
    }

    n += p.write('}');

    return n;
}

JsonValue& JsonObjectBase::operator[](char const* key)
{
    for (int i = 0; i < count; ++i)
    {
        if (!strcmp(items[i].key, key))
        {
            return items[i].value;
        }
    }

    if (count >= capacity)        
        return JsonValue::null();
    
    items[count].key = key;
    return items[count++].value;
}