#Popiel Michał Wojciech

##Program — survival mieszczucha w dżungli.

Mieszczuch, posiadający kilka całkowicie zaspokojonych potrzeb, ( zdrowie, głód, pragnienie, sen ) zostaje porzucony w dżungli. Minie 30 dni(tur, kolejek) zanim odnajdzie go ekipa ratunkowa. Jego zadaniem jest przeżyć do tego momentu. Wraz z upływem czasu mieszczuch bardzo szybko zaczyna potrzebować jedzenia, snu, schronienia itd. 

Podejmuje więc różne akcje takie jak _poszukiwanie jedzenia_, _poszukiwanie schronienia_ itp. zależne od tego czego mu w danym momencie najbardziej brakuje, a także od pory dnia. Akcje mogą zakończyć się powodzeniem lub fiaskiem z odpowiednim prawdopodobieństwem. W przeżyciu mieszczucha przeszkadzają najróżniejsze zdarzenia losowe:

- dzikie zwierzęta, 
- zanieczyszczona woda, 
- kanibale 
- itd. 

Mogące wystąpić z odpowiednim prawdopodobieństwem w zależności od akcji mieszczucha i pory dnia. 

Program wyświetla podsumowania codziennego zmagania mieszczucha z przyrodą wraz z informacją czy udało mu się przeżyć. Może zostać potem rozbudowany np. o więcej osób i możliwość współpracy między nimi lub zdolność mieszczucha do podejmowania coraz lepszych decyzji bazując na posiadanej umiejętności _survival_ zwiększanej proporcjonalnie do okresu pobytu mieszczucha w dżungli.

-------------------------------------------------
Instrukcja do pliku csv:
- pierwsze 3 akcje są zarezerwowane jako akcje człowieka.
- wiersze <4,99> są zarezerwowane na "negatywne dla człowieka" reakcje natury.
- wiersze <100, 199> są zarezerwowane na "pozytywne dla człowieka" reakcje.
- wiersze <200+) są akcjami DŁUGOTERMINOWYMI, mającymi skutki w przyszłości, mogą się one pojawić jako dodatek do akcji/reakcji.
 
AKCJA składa się z:

 (id),(nazwa),(wpływ na zdrowie),(wpływ na napojenie),(wpływ na sytość),(wpływ na wypoczęcie),(szansa wystąpienia w dzień),(szansa wystąpienia w nocy),(typ możliwej akcji długoterminowej),(szansa na akcję długoterminową)

AKCJA DŁUGOTERMINOWA składa się z:

 (id),(komunikat1),(wpływ na zdrowie),(wpływ na napojenie),(wpływ na sytość),(wpływ na wypoczęcie),(szansa wystąpienia),(podstawowa długość trwania),(typ możliwej kolejnej akcji długoterminowej),(szansa na akcję długoterminową),(typ),(komunikat2),(kolejne dni trwania)