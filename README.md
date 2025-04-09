# VRG vstupní demo C++

## Simulátor střelby s použitím vnější balistiky

Zadání:

- vstup:
    - 3D bod umístění střelce (terén je rovná deska začínající v `[0,0,0]`)
    - 3D bod umístění cíle (může být v různé výšce)
    - úsťová rychlost střely
    - hmotnost střely
    - délka simulačního kroku
- výstup:
    - úhel náměru, při kterém je cíl zasažen (pokud lze dostřelit)

- lze zanedbat veškeré složitosti (stačí jednoduchá fyzika hmotného bodu v konstantním gravitačním poli)
- atmosféru lze uvažovat s konstantní hustotou ve všech výškách
- **použijte ECS (Entity-Component-System) "návrhový vzor"** - ideálně knihovnu `EnTT` (https://github.com/skypjack/entt)
- GUI není nutné (stačí výpis průběhu s nějakým krokem)
- navrhněte nějakou formu otestování vstupu/výstupu (např. přes nějaký unit-test framework ... my používáme `catch2`)
- lze použít `c++23` a libovolné, Vámi zvolené, technologie a knihovny

**Smyslem úkolu není tvorba dokonalého simulátoru (neočekáváme 100% funkčnost), ale ukázka vašeho přístupu k řešení problému a práce s kódem.**

---

Výsledný kód pošlete prostřednictvím odkazu na public git repozitář (např. GitLab nebo GitHub)
