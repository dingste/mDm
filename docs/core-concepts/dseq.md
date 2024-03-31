das IPO paradigma ist selbstklärend. dennoch sollten einige begrifflichkeiten erwähnt und erklärt werden. Wie die: dSeq, or direct sequence, represents the structured execution flow in mDm, encompassing the IPO model's phases within a single construct.
  ```mDm
  data, process, result
  ```

dSeq (direct sequence)s bestehen immer(!) aus den 3 schritten:
 dSeq (direct sequence) = EINGABE, VERARBEITUNG, AUSGABE
trennung der schritte durch ,. die schritte werden dState genannt.
dSeq (direct sequence)s sind in sich geschlossen und es wird immer von einem dState sequenziell in dieser reihenfolge zum nächsten gesprungen. somit steht die eingabe oder parameter für eine operation vor der verarbeitung. das ergebnis der verarbeitung liegt instantan am ausgang an.
dSeq (direct sequence)s können geklammert werden (EINGABE, VERARBEITUNG, AUSGABE) um sie verschachtelt in anderen dSeq (direct sequence)s zu verwenden.
dSeq (direct sequence)s ist der einzige und fundamentale rechenschritt.
in diesem sinne ist eine typendefinition, eine funktion oder ein ganzes programm eine immer eine dSeq.
dSeq kann für deklerative zwecke benutzt werden oder auch zur implementierung. im programmier kontext unterscheiden sich die beiden:
dekleration: (eingabetypen),funktionsname,(ausgabetypen)
implementation: (eingangsvariabeln),(process logik), funktionsname

verschachtelung in der form:
((dState, dState, dState), dState, dState)
oder:
((dSeq, dState, dState), dSeq, dState)
sind möglich und erweitern die funktionalität der sprache. Der OUTPUT dState der einen dSeq kann an anderer Stelle oder in einem anderem Programmteil mit benutzt werden.

Defining a sequence with input, process, and output.
  ```mDm
  (inputData), performCalculation, outputData
  ```
  