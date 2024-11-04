# Philosophers

The **Philosophers** project is an implementation of the classic dining philosophers problem, which explores concurrency issues like deadlock and resource sharing. In this simulation, multiple philosophers sit at a round table with a bowl of spaghetti in the center, attempting to alternate between thinking, eating, and sleeping without starving.

## Table of Contents
- [Project Overview](#project-overview)
- [Rules and Constraints](#rules-and-constraints)
- [Compilation](#compilation)
- [Usage](#usage)
- [Simulation Output](#simulation-output)
- [Example](#example)

![Philosopher Image](./assets/images(1).jpng)

## Project Overview

The project simulates philosophers trying to eat spaghetti without dying of starvation. This README provides the necessary information to understand, build, and run the simulation.

## Rules and Constraints

### Simulation Rules

- Philosophers are seated around a circular table, with a large bowl of spaghetti in the center and one fork per philosopher.
- Each philosopher must hold two forks (their left and right) to eat.
- Philosophers alternate between **eating**, **thinking**, and **sleeping**:
  - While eating, they are not thinking or sleeping.
  - While sleeping, they are not eating or thinking.
  - While thinking, they are not eating or sleeping.
- When a philosopher has finished eating, they put down their forks and begin sleeping.
- The simulation stops if a philosopher dies of starvation.
- Philosophers do not communicate with each other, nor do they know if another philosopher is about to die.

### Global Rules

- The program accepts the following command-line arguments:
  - `number_of_philosophers`: Number of philosophers (and also the number of forks).
  - `time_to_die` (in ms): Maximum time a philosopher can go without eating before dying.
  - `time_to_eat` (in ms): Time taken to eat.
  - `time_to_sleep` (in ms): Time spent sleeping.
  - `number_of_times_each_philosopher_must_eat` (optional): If specified, the simulation stops when all philosophers have eaten at least this many times. If omitted, the simulation stops when a philosopher dies.
- Each philosopher is assigned a unique number (from 1 to `number_of_philosophers`).
- Philosophers are arranged in a circular manner: Philosopher 1 sits next to Philosopher `number_of_philosophers`, and each other philosopher sits between two others.

### Logging Rules

- All state changes of philosophers must be logged in the format:
  ```
  timestamp_in_ms X has taken a fork
  timestamp_in_ms X is eating
  timestamp_in_ms X is sleeping
  timestamp_in_ms X is thinking
  timestamp_in_ms X died
  ```
  - A message about a philosopher’s death should be displayed within **10 ms** of the actual event.

## Compilation

To compile the project, run:

```bash
make
```

This will create an executable for the philosopher simulation.

## Usage

To run the philosopher simulation, use the following syntax:

```bash
./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

- **Arguments**:
  - `<number_of_philosophers>`: Total philosophers and forks at the table.
  - `<time_to_die>`: Time in milliseconds after which a philosopher dies without eating.
  - `<time_to_eat>`: Time in milliseconds required for a philosopher to eat.
  - `<time_to_sleep>`: Time in milliseconds a philosopher spends sleeping.
  - `[number_of_times_each_philosopher_must_eat]`: Optional argument. If provided, the simulation stops after each philosopher has eaten at least this many times. Otherwise, the simulation stops upon a philosopher’s death.

### Example Command

```bash
./philosophers 5 800 200 200
```

This command will start a simulation with 5 philosophers, each having 800 ms before they die of starvation, 200 ms to eat, and 200 ms to sleep.

## Simulation Output

The output logs will display each philosopher’s actions, formatted as specified. For example:

```
120 1 has taken a fork
120 1 has taken a fork
120 1 is eating
320 1 is sleeping
520 1 is thinking
...
```

## Example

Here’s a sample execution of the program with example output:

```bash
$ ./philosophers 4 500 200 200 3
```

Expected Output:

```
100 1 has taken a fork
101 1 has taken a fork
102 1 is eating
300 1 is sleeping
501 1 is thinking
...
```

The simulation will continue until either all philosophers have eaten the specified number of times or one philosopher dies.

## Project Notes

- This project is a classic concurrency problem and tests knowledge of mutexes, semaphores, and timing in C.
- **Deadlock Prevention**:
  - To avoid deadlock, this project implements **Dijkstra’s solution** for the dining philosophers problem. This approach ensures that each philosopher only picks up forks when both are available, preventing the classic deadlock scenario where each philosopher holds one fork and waits indefinitely for the other.
  - Additionally, **staggered start times** are used based on philosopher IDs:
    - Philosophers with odd-numbered IDs start their routines slightly later, allowing forks to be available in a non-simultaneous pattern. This staggered approach further helps prevent contention and starvation.
      
- **Concurrency Challenges**:
  - Be mindful of potential **deadlocks** and **starvation issues** when working with shared resources (forks). Using mutexes and carefully structuring the timing logic helps ensure that each philosopher has a fair chance to eat without blocking indefinitely.
    
- **Routine Execution**:
  - Each philosopher follows a sequential routine: **eating**, **sleeping**, and **thinking**, with each state change logged precisely to track philosopher status.
  - For simulations with a single philosopher, a specific routine is used to manage the single available fork, as they cannot eat with only one fork.

--- 

