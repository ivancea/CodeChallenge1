from datetime import date
from babel.dates import format_date
from babel import languages, Locale
import sys

def get_locale(locale_str):
    if locale_str != 'CA':
        languages_by_territory = languages.get_official_languages(locale_str)

        if languages_by_territory:
            return languages_by_territory[0]

    try:
        locale = Locale.parse(locale_str)
        
        if locale.territory is None:
            return locale.language

        return locale.language + '_' + locale.territory
    except:
        return None


cases = int(input())

# Read all cases with the format "date:locale"
for i in range(cases):
    case = input()
    case_parts = case.split(':')

    locale_str = case_parts[1]

    date_parts = case_parts[0].split('-')
    day = int(date_parts[0] if int(date_parts[0]) < 1000 else date_parts[2])
    month = int(date_parts[1])
    year = int(date_parts[2] if int(date_parts[0]) < 1000 else date_parts[0])
    try:
        case_date = date(year, month, day)
    except ValueError:
        case_date = None

    locale = get_locale(locale_str)

    if case_date is None:
        print("Case #" + str(i + 1) + ": INVALID_DATE")
    elif locale is None:
        print("Case #" + str(i + 1) + ": INVALID_LANGUAGE")
    else:
        formatted_date = format_date(case_date, format="EEEE", locale=locale).lower()
        if locale_str == 'FI':
            formatted_date = formatted_date[:-2]
        if locale_str == 'RO':
            formatted_date = formatted_date.replace('ț', 'ţ')
        
        print("Case #" + str(i + 1) + ": " + formatted_date)