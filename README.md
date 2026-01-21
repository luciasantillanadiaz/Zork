# My Zork: Castle Escape

A text-based adventure game written in C++. Explore a haunted castle, solve puzzles, and escape before the vampire catches you.

**Link to Repository:** [Zork](https://github.com/luciasantillanadiaz/Zork)

## About the Game
You wake up in the Great Hall of a dark, decaying castle. Your memory is hazy, but one thing is clear: you must escape. To do so, you will need to find items, unlock hidden paths, and solve the mystery of the Chapel. But be careful... you are not alone.

**Authors:** Lucía Santillana Díaz

## How to Play

### Controls
Type your commands into the console and press **Enter**. The game is case-insensitive (you can use `LOOK` or `look`).

**Movement:**
* `north` / `n`: Move North
* `south` / `s`: Move South
* `east`  / `e`: Move East
* `west`  / `w`: Move West
* `up`    / `u`: Go up stairs
* `down`  / `d`: Go down stairs

**Actions:**
* `look` / `l`: Look at the room or examine an item (e.g., `look sword`).
* `take [item]`: Pick up an item (e.g., `take key`).
* `drop [item]`: Drop an item from your inventory.
* `inventory` / `i`: Check what you are carrying.
* `open [barrier]`: Open a door, chest, or container.
* `unlock [barrier] with [key]`: Unlock a locked door/container using a specific key.
* `place [item] in [container]`: Put an item inside a specific container/pedestal.
* `attack` / `attack [enemy]` / `attack with [weapon]` / `attack [enemy] with [weapon]`: Attack an enemy.
* `quit` / `q`: Exit the game.

---

## Walkthrough (Guide to Finish)

<details>
  <summary>How to pass the game step by step</summary>

1.  **Start:** You are in the **Great Hall**.
2.  Go **West** to the **Banquet Hall**.
3.  `take sword` (Attack with this).
7.  `take stake`.
4.  Go **North** to the **Kitchen**.
5.  `take garlic`.
6.  Go **South** back to the **Banquet Hall**.
8.  Go **East** to the **Great Hall**.
9.  Go **North** up the **Stairs**.
10. Go **North** to the **Aisle**.
11. Go **West** to the **Main Chambers**.
    * *Warning:* The **Vampire** is usually here, but it can move to other rooms. He has too much health to kill, but you can stun him with enough damage. 
12. `open drawer`.
13. `take key` (This is the key for the Tower).
14. Go **East** back to the **Aisle**.
15. Go **East** to the Tower door.
16. `unlock door with key`.
17. `open door`.
18. Go **East** into the **Tower**.
19. `take cross`.
20. `take relic`.
21. Go **West** to **Aisle**, then **South** to **Stairs**, then **South** to **Great Hall**.
22. Go **East** to the **Library**.
23. `unlock trapdoor with relic`.
24. `open trapdoor`.
25. Go **Down** to the **Chapel**.
26. You will see three pedestals. You must place the correct items to solve the puzzle:
    * `place cross in cross-pedestal`
    * `place garlic in circle-pedestal`
    * `place stake in triangle-pedestal`
27. The box unlocks.
28. `open box`.
29. `take gate-key`.
30. Go **Up** to **Library**, then **West** to **Great Hall**.
32. `unlock gate with gate-key`.
33. `open gate`.
34. Go **South** to **The Exterior**.

**CONGRATULATIONS! YOU HAVE ESCAPED!**

</details>

---

## License

MIT License

Copyright (c) 2026 Lucía Santillana Díaz 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
