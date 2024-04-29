# 1340Group2
## 测试模块：

目前已包含的测试模块：
- maze/maze
  - `make maze`
- character/monster
  - `make monster`
- character/character
  - `make character`
- utils/utils
  - `make utils`
- ui/start
  - `make start`
- ui/saving_ui
  - `make saving_ui`
- clean
  - `make clean`

# For Player
## Team members 🧑‍💻 ( In alphabetical order )
[Liu Boyuan]()&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;(3036128315)

[Lyu Wenzhuang]()&ensp;&ensp;&ensp;&ensp;(3036128004)

[Qiu Xuze]()&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp; (3036128169)

[Xu Qiyue]()&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp; (3036127359)

[Zhang Shenru]()&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;(3036128157)

## How to play 🤗
### Quick DEMO
[![asciicast]()](video link)

**Remember to zoom in the terminal window to get a better experience.**
```bash
make game
```
```bash
./game
```
### Small Tips Here!
    - Numerical-related Concepts

    There is a chance for a character to be immune to damage when they are attacked. There is also a probability for a character to land a critical hit or a double critical hit when they deal damage.
    [MP]: Skills released by [Character] or [Monster] consume MP.
    [Evasion Rate]: The probability of avoiding damage when being attacked.
    [Critical Rate]: The probability of landing a critical hit when dealing damage.
    [Critical Damage]: The ratio of the damage caused by a critical hit to the original damage.

    Basic Mechanics

    [Combat]: When [Character] encounters [Monster] while moving through the maze, they enter into combat. If [Character] fails, the game ends.
    [Growth]: By defeating a certain number of enemies, [Character] can level up. Upon leveling up, their health is restored to maximum, and their base stats increase. Additionally, at levels 1, 4, 7, and 10, they can choose either an active or passive skill.

    Combat Mechanics

    Attack Mechanism: [Character] and [Monster] take turns attacking, using either a basic attack or a skill each round.
    MP Restoration Mechanism: When receiving damage, a certain amount of MP is restored. MP is consumed when using skills.
    Monster Skill Release: [Monster] releases an active skill every three rounds. If there is insufficient MP, the skill will be canceled.

    Types of Monsters:

    [Clone]: Basic monsters created based on the bounty hunter Jango Fett with moderate health, attack, and defense. Their attacks have a lifesteal effect based on the damage dealt.
    [Sith]: Force users with a belief in the dark side of the Force with low health and defense. They possess the active skill [Return to Dark], which grants invincibility and increased critical hit chance while active. When the effect ends, the Cith dies.
    [Robot]: High-tech creations of the empire. They have high defense and possess the active skill [Laser], which deals high damage.
    [Mandalorians]: An ancient humanoid species that values combat skills with high attack and defense. They possess the active skill [Rage], which increases their attack and grants them an opportunity to perform a [Beatback] counterattack, reflecting the full amount of damage received in the next attack.


## Features implemented 🚀
- **Generation of random game sets or events**

    - We use static `std::mt19937 rng(std::random_device{}())` to generate random walls and `std::pair<int, int> randomPosition()` to generate monsters and exits. This random generator uses the seed generated by hardware devices and can generate high-quality random numbers throughout the entire lifecycle of the program.
⁣⁣⁣⁣
- **Data structures for storing game status**

    - We define a struct to store the game status (refer to struct save_file in src/ui/start_endpage.h). This struct is used to communicate with the sav.txt that stores the game status and to manage the flow of games. In addition, we also define a number of classes to effectively manage characters, monsters and maze. They enables high modularity for easier troubleshooting and effective reuse of code. We can easily locate bugs and fix them within a second!
⁣⁣⁣⁣
- **Dynamic memory management**

    - The variable `save_parameters` is defined using the `new` keyword. We can pass the pointer between functions and access this memory even after the original function returns.
⁣⁣⁣⁣
- **Save progress**

    - One of the key features of this game is the ability for players to perform save operations easily by clicking 'e' and continue from their saved progress in the next gaming session.
    Each saving slot comprises of the username and a corresponding level number. This design can allow players to locate the wanted game progress quickly.
    Also, we save every progress in a file and the file will be parsed/updated on time, so players don’t need to worry that they will risk losing progress even after they quit the whole game.

⁣⁣⁣⁣
- **Program codes in multiple files**

    - Easy to manage and modify different functions of the game
⁣⁣⁣⁣
- **Proper indentation and naming styles**

    - The meanings of each variables and functions are very explicit. We can quickly locate the function that needs to be modified.
⁣⁣⁣⁣
- **In-code documentation**

    - We won't lose our way with a lot of code.


## Description 😎
💎Welcome to our text-based Star Wars game written in C++! We're excited to bring the Star Wars experience to life in a unique and engaging way. In this game, you will embark on an adventure to defeat the Imperial forces and become the ultimate Jedi Master (Really?). Don't forget to try to defeat all the Imperial forces!

🎢At the start of your journey, you'll get your starting lightsaber and set out into the world. You'll explore various locations such as grasslands, rivers, and hills, where you'll encounter Imperial forces. Each time you defeat an enemy, you'll gain exps, which will help you level up and unlock new abilities.

👾When you come across the Imperial forces, you'll have the opportunity to battle them. Battles are turn-based and consist of four main options: attack, defend, use your special skills, or flee. You'll choose your options and watch as your Jedi apprentice battles against the Imperial forces.

🕹️As you progress through the game, you'll defeat new Imperial forces, each with their own unique abilities and attributes.

🏆Your ultimate goal is to become the Jedi Master by defeating the most powerful bosses. Only the most skilled and dedicated players will be able to rise to the top face emperor Palpatine.

😜Our game is fun and challenging and will keep you engaged for hours on end. With its simple yet addictive gameplay and nostalgic feel, we're sure it will appeal to fans of the original Star Wars games. So go ahead and enjoy it!

## Non-standard libraries 🗂️
Not used, standard libraries only.

