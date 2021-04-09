# Projektplanung

## Glosar
- MR: Merge Request

## Allgemeines
- Zusatzaufgabe: Embedded Recorder/ Replay

## Tools
- UML
  - UMLet 
  - optional Yakindou für statemachines

## Git 
- Master branch
- Feature branches
  - wie erstellen? am leichtesten siehe [Abschnitt Gitlab](#Gitlab)
  - Keine Angst vor neuen Branches
- Häufig commiten
  - Aussagekräftige Commit-messages: TBD

## Gitlab
- Plannung
  - Tasks als Gitlab Epics
  - Subtasks und sonstiges als Gitlab Issues
  - Zusammengesetzte Subtasks als Subepics
- Wenn was zu tun ist
  1. Issue erstellen
  2. Asignee zuordnen
  3. Falls langläufig: Milestone und Epic zuordnen
  4. Feature-Branch erstellen, wenn nötig (nicht jedes Issue braucht einen Branch: zB: Issue "Fix some bug with feature A", wenn ein "Feature A" Branch besteht)
  - Konzept: Draft MR
    - Für einen Feature Branch direkt ein MR mit "*Draft:*-prefix" aufmachen. So kann man leicht sehen welche Änderungen für dieses Feature schon vorgenommen wurden. Außerdem lassen sich im MR direkt Kommentare usw. sammeln. 
  - Zum erstellen eines Feature-Branches auf der Issue-Seite auf *Create merge request* klicken, dann wird ein neuer Branch mit passenden Namen und mit einer Referenz zum Issue erstellt ("Closes #[id] in der desc.). Der Erstellte MR hat im Titel den Prefix *Draft*, sobald das Feature fertig ist muss auf *Mark as ready* geklickt werden, erst dann kann gemerged werden (wenn genügende approves da sind).
   Alternativ Branch über CLI erstellen, dann auf passenden Namen achten.
- [Requirements auf Gitlab](https://git.haw-hamburg.de/ss21-esep-gruppe-2.3/esep/-/requirements_management/requirements)
- Codereviews: Code checken -> "I approve" bedeutet **du bist verantwortlich** dafür dass alles läuft

## Testen
- Testcases so früh wie möglich bestimmen

## Rollenerteilung
siehe [README](README.md)

