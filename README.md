# ⚡ FSM Reaction TImer (Arduino | FSM Learning Project)

This project started as a **simple reaction timer idea** and evolved into a **deep dive into embedded systems fundamentals**.

Instead of focusing only on the final output, this repository documents the **learning journey** behind building a reliable, non-blocking, state-driven Arduino project.

---

## 🧠 Why This Project?

At first glance, a reaction timer sounds trivial.  
But building it *correctly* exposed several real-world embedded challenges:

- How do you handle time **without blocking** the CPU?
- How do you prevent **false button presses**?
- How do you design logic that doesn’t collapse as complexity grows?
- How do you structure code so behavior is predictable?

This project exists to answer those questions.

---

## 🧭 Learning Journey (Step-by-Step)

### 🔹 Step 1: Naive Thinking
The initial instinct was:
- Use `delay()` for waiting
- Check `if(buttonPressed)`
- Move sequentially from one action to another

This approach **failed immediately**:
- Buttons triggered multiple times
- False starts weren’t detectable
- The system became unresponsive during delays

➡️ **Lesson:** Embedded systems cannot rely on blocking logic.

---

### 🔹 Step 2: Discovering FSM (Finite State Machine)

The project was restructured into a **Finite State Machine (FSM)**.

Instead of “doing things in order”, the system now:
- Always knows **which state it is in**
- Decides behavior based on the current state
- Transitions cleanly between states

Defined states:
- `IDLE` – waiting for user intent
- `WAIT` – random delay + false start detection
- `ACTIVE` – reaction time measurement
- `RESULT` – outcome handling

➡️ **Lesson:** FSMs turn messy logic into predictable systems.

---

### 🔹 Step 3: Non-Blocking Timing with `millis()`

Using `delay()` froze the system and prevented input checks.

The fix:
- Store timestamps
- Compare `currentTime - startTime`
- Never pause the CPU

This allowed:
- Continuous button monitoring
- Accurate reaction timing
- Reliable false start detection

➡️ **Lesson:** Time should be *checked*, not *waited for*.

---

### 🔹 Step 4: Button Edge Detection (The Game Changer)

A single button press produced **multiple signals** due to mechanical bouncing.

Solution:
- Track previous button state
- Detect only the **transition** (edge)
- React once per press

This stabilized the FSM completely.

➡️ **Lesson:** In embedded systems, **events matter more than levels**.

---

### 🔹 Step 5: Hardware Constraints & Communication

Only **one LED** was allowed.

Instead of adding hardware:
- LED behavior was reused intelligently
- Different states were indicated using timing & patterns

➡️ **Lesson:** Good design adapts to constraints instead of avoiding them.

---

## 🚀 Final Features

- ⏱ Reaction time measurement (ms)
- 🚫 False start detection
- 🔁 FSM-based architecture
- 🧠 Edge-detected button handling
- ⛔ Fully non-blocking (`millis()`)
- 💡 Single-LED multi-state indication
- 🖥 Serial Monitor debugging

---

## 🛠 Hardware Used

- Arduino Uno / Nano  
- 1 × LED  
- 2 × Push Buttons  
  - Session Button (Start / Reset)
  - Reaction Button  
- Resistors, breadboard, jumper wires  

---

## 🔌 Pin Configuration

| Component        | Arduino Pin |
|------------------|-------------|
| LED              | D12         |
| Session Button   | D11         |
| Reaction Button  | D10         |

Buttons use `INPUT_PULLUP`.

---

## 🧠 System Architecture (FSM Overview)
IDLE → WAIT → ACTIVE → RESULT → IDLE

........................↘ (false start) ↗

Each state has:
- Clear responsibility
- Defined valid inputs
- Explicit transitions

No state blocks execution.

---

## 🧪 What This Project Taught Me

- How to **think like an embedded engineer**
- Why FSMs are essential for scalable logic
- Why `delay()` is dangerous in real systems
- How hardware imperfections affect software
- How to design under constraints

---

## 📈 Future Improvements

- Multiple rounds with average & best reaction time
- LCD / OLED display
- Buzzer feedback
- Interrupt-based input handling
- ESP32 / RTOS version

---

## 🧑‍💻 Author

**Sian Soj**  
Electronics & Communication Engineering Student  
Exploring Embedded Systems, IoT, and Hardware Prototyping  

---

## 📜 License

Open-source.  
Free to learn from, modify, and build upon.

