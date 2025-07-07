# 🎓 RPG-University

A text-based RPG about university student life, written in C.  
Manage your time, attend classes, study (or not), go to parties, and try to survive the semester!

> ⚠️ **Note**: The game is fully written in **Portuguese (Brazilian)**.

---

## 🕹️ How It Works

- The player starts by choosing a **name** and **subjects** for the semester, each with a class schedule: `morning`, `afternoon`, or `evening`.

- Each **day is divided into 4 time slots** (called "day moments"). You can perform **one action per time slot**.

- All subjects require **minimum XP and attendance** to be passed.

- The game has random events so be careful

---

## 🎯 Actions & Their Effects

- **Go to college**
  - Attending classes grants XP in all subjects scheduled for that time slot.
  - XP is randomly assigned (never less than 3).
  - You gain attendance for all relevant subjects.

- **Study**
  - Gain XP in subjects of your choice.

- **Sleep**
  - Removes most status effects (debuffs).

- **Go to bar/party**
  - Unlocks a sub-menu with more actions:
    - Chat with friends
    - Play pool
    - Drink beer (excessive drinking causes the `drunk` debuff)
    - Go out
  - Before each action, there is a chance of a **random event** (positive or negative) and you might **meet new people**.

- **See status**
  - Shows your current XP, attendance, and debuffs.

- **Go on a date** *(unlocked after meeting someone at bar/party)*
  - You can build relationships and unlock events.

- **Early Morning** (4th time slot)
  - If used, causes the `tired` debuff.

---

## ⚠️ Status Effects (Debuffs)

You can gain debuffs from specific actions or random events. Examples include:

- `tired`
- `drunk`
- `hurted`
- `sick`
- Others to be added...

---

## 📆 Semester Length

- The game lasts **30 in-game days**.
- At the end, you'll see whether you passed or failed each subject.

---

## 🚧 Current Limitations

- The dating system is **not fully implemented** yet.
- Bugs may occur — feel free to report them in the issues section!

---

## 🛠️ Tech Info

- Language: **C**
- Style: **Text-based RPG**
- Platform: Terminal/Console

---
