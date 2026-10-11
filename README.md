<img width="959" height="476" alt="Screenshot 2026-10-11 221911" src="https://github.com/user-attachments/assets/6f49e2ac-377d-4caf-a8c0-df513e80e42a" />

## Assignment B: Class 4 Code Debugging
**Issue Found:** 
After analyzing the circuit behavior, a logic bug was identified in the final `else` block of the code. This block (intended for when the area is clear or out of range) mistakenly contained the exact same `tone()` and `delay()` commands as the moderate distance warning block. Because of this error, the buzzer looped its warning beeps continuously and never actually silenced itself when an object left the sensor's range.

**How it was Solved:**
All `tone()` and `delay()` commands were deleted from the final `else` block and replaced with a single `noTone(buzzerPin);` command. This ensures the system remains completely silent when no object is detected.

**Code Explanations:**
A complete, line-by-line explanation of the program logic and hardware control sequence has been documented directly as comments within the `Assignment_B.ino` file.
