What is it:
This small project is a simulation of Mitchie's educatable matchboxes, or Matchbox Educable Noughts and Crosses Engine (MENACE), which is a fascinating early example of artificial intelligence and machine learning, built in 1961 by British computer scientist Donald Michie. It wasn't actually a computer in the traditional sense, but rather an ingenious mechanical contraption made from 304 matchboxes. Each matchbox represented a single possible state of a tic-tac-toe (noughts and crosses) game board. By flipping switches inside the boxes, Michie could simulate playing a game and explore different potential moves.

How does it work:
When playing against a human opponent, MENACE would initially choose moves randomly. For each game, it would keep track of the outcome. If a particular move led to a win, the corresponding matchbox would get a "positive" reinforcement, making it more likely to be chosen again in the future. Conversely, moves that led to losses would be discouraged.

Over time, as MENACE played more games, it would gradually learn to play tic-tac-toe at a higher level. It could adapt its strategy to different opponents and even develop its own unique style of play.

My own version:
I was fascinated with this simple yet effective model of machine learning, which led to creating my own version of it. Through simple C++ code, I have created the matchboxes machine, where the matchboxes are represented by objects of a class that hold the state of the game and the possible moves. The class coordinator is responsible for performing the actual actions, such as looking for the current state of the game and making a decision based on the saved data.

Additionally, I wrote another file of the code ‘generatePatterns’ to generate every possible state of the tic-tac-toe game, which MENACE will use to make the decisions and learn.





