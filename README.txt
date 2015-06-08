Labyrinth:
Das Labyrinth besteht aus 4fach verknüpften Knoten (für jeden anliegenden Knoten eine Verknüpfung). Jede Wand wird durch einen nullptr dargestellt, wenn ein Weg vorhanden ist wird ebendieser Knoten der entsprechenden Himmelsrichtung zugewiesen.
Die Knoten werden in einem zweidimensionalen Vector gespeichert.
Beim Einlesen des Labyrinthfiles wird zuerst überprüft wie breit das Labyrinth ist. Da alle Labyrinthe quadratisch sind, wird die Höhe auf den selben Wert gesetzt. Dann wird eine doppelte for-Schleife gestartet die Zeichen für Zeichen, Zeile für Zeile einließt. Bei jedem " " wird an dieser Stelle im Vektor ein neuer Knoten angelegt, bei einem "#" bleibt diese stelle ein nullptr.
Nach dem einlesen des Labyrinths werden die Verknüpfungen erstellt. Es wird durch jeden Knoten durch iteriert und anhand der Vektorposition verknüpft.
Danach werden Start- und Endpunkt gesucht: Im Uhrzeigersinn oben links anfangend, das erste Element des Vectors, dass kein nullptr ist wird der Eingang, das zweite der Ausgang.
Sobald Das Labyrinth fertig verknüpft ist und Eingang und Ausgang gefunden sind werden je nach gesetzten Options die Roboter in eigenen threads gestartet. Am Ende dieser Funktion wird ausgegeben wieviele Schritte jeder Roboter benötigt hat.

Roboter:

robot_left:
Dieser Roboter versucht nach jedem Schritt zuerst nach links abzubiegen, wenn das nicht funktioniert, versucht er gerade aus weiter zu gehen. Sollte das auch fehlschlagen probiert er nach rechts abzubiegen, funktioniert dies nicht, dreht er sich um und geht einen Schritt nach vorne. Dieses Muster wird solange wiederholt, bis der Roboter am Ziel angekommen ist.

hubot:
Dieser Roboter sucht den Ausgang per Tiefensuche. Wenn er auf einem Feld steht und die Felder um ihn begehbar sind, wird die Funktion rekursiv aufgerufen. Jedes mal wenn der Roboter auf einem neuen Feld steht wird es in einem Array gespeichert damit man abfragen kann ob dieses Feld bereits betretetn wurde. Wenn er merkt das er in einer Sackgasse ist, wird die Funktion beendet. Sobald er den Ausgang gefunden hat wird ein bool auf true gesetzt damit er in den neuen aufgerufen Rekursionen nicht mehr weitersucht.

right_left:
Dieser Roboter versucht nach jedem Schritt zuerst nach rechts abzubiegen, wenn das nicht funktioniert, versucht er gerade aus weiter zu gehen. Sollte das auch fehlschlagen probiert er nach links abzubiegen, funktioniert dies nicht, dreht er sich um und geht einen Schritt nach vorne. Dieses Muster wird solange wiederholt, bis der Roboter am Ziel angekommen ist.
