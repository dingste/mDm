Loop constructs in mDm facilitate iterative operations within the IPO model.

- **mDm Example**: Looping through a list.
  ```mDm
  (_, (index; size(myList)), while <, (myList[index], processItem, _)), _
  ```

##### Looping with conditions

mDm introduces a unique syntax for conditional statements and loops, maintaining its commitment to the IPO structure while accommodating control flow mechanisms essential for practical programming. These constructs allow developers to implement decision-making and iterative processes within the rigid framework of dSeq (direct sequence)s, striking a balance between structure and flexibility.

'for'-schleifen sind nicht notwendig. mit 'while' lassen sich alle
bedingungen und schleifenkörber konstrukte abbilden.

[Loop with while](snippets/looping.mDm)

Loops in mDm are implemented through dSeq (direct sequence)s that specify the conditions for iteration. The language uses a structured approach to define loop conditions and actions, aligning with the IPO model. For instance, a `while` loop construct might look like this:

This example demonstrates a loop that increments `counter` until it is less than 10, showcasing how loop conditions and bodies are defined within the dSeq (direct sequence) framework.
Looping is a fundamental aspect of programming, allowing for repeated execution of a block of code. This example outlines a simple loop structure in mDm.

Here, the `while <` construct illustrates how mDm implements loops, using its structured syntax to define loop conditions and actions clearly.
