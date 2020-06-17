# Utilitaire de gestion du son

## Description des classes
### SoundRef
La classe **SoundRef** permet de déclarer une collection de sons à laquelle il est possible d'appliquer des options d'exécution : 
```js
new SoundRef(source: string|Array [, options: {}])
```
L'argument **source** accepte une *string* si la collection ne contient qu'un seul son, ou bien un *tableau de string* pour ajouter plusieurs sons.
Les sons doivent être dans un dossier /sounds à la racine du projet, il sera automatiquement copié dans le dossier output à la compilation. Attention, la copie n'a lieu qu'à la première compilation ngon. Pour re-provoquer la copie, il suffit de relancer ngon et de re-compiler.

L'argument facultatif **options** est un objet, acceptant les propriétés suivante:
```js
{
	loop: true|false, // Si vrai, les sons sont automatiquement joués les uns après les autres
	random: true|false, // Si vrai, le son joué est choisi aléatoirement
	procedural: true|false, // Si vrai, le son joué est choisi aléatoirement avec un tirage dans remise
	streamsLimit: Number // Indique le nombre de sons d'une même collection qui peuvent être joué en même temps, vaut 1 par défault.
}
```
Par défaut, toutes les options sont à ***false***.

### Manager
La classe **Manager** permet de jouer les objets **SoundRef**. Le **Manager** est ciblé comme ceci:
```js
pg.sound.Manager
```

#### Méthodes
##### register
```js
pg.sound.Manager.register(id: string|number, ref: SoundRef);
```
Une fois l'object **SoundRef** instancié, il doit être enregistré dans **Manager** avec la méthode *register*. Il faut lui associer un ***id*** unique.

```js
const ref = new pg.sound.SoundRef(['hello.mp3', 'goodbye.mp3'], {loop: true});
pg.sound.Manager.register('greetings', ref);
```

##### play/pause/stop
```js
pg.sound.Manager.play(id: string|number);
pg.sound.Manager.pause(id: string|number);
pg.sound.Manager.stop(id: string|number);
```
**play**, **pause** et **stop** permettent de respectivement jouer une référence, la mettre en pause ou l'arrêter.

```js
pg.sound.Manager.play('greetings');
pg.sound.Manager.pause('greetings');
pg.sound.Manager.stop('greetings');
```

##### stopAll
```js
pg.sound.Manager.stopAll();
```
Arrête la lecture de tout les sons en lecture, de toutes les références enregistrés.

##### muted
```js
pg.sound.Manager.muted = bool;
```
La propriété **muted** coupe ou remet le sonde la scène.

```js
pg.sound.Manager.muted = true; // coupe le son
pg.sound.Manager.muted = false; // réactive le son
```

Note : a priori il n'est pas nécessaire d'utiliser cette méthode, car c'est plutôt la responsabilité du controller de le faire.