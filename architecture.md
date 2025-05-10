# Protocol

## Client

Puede enviar todos estos requests:

- Crear nombre de usuario

    0x01 <length-username> <username>
    
    siendo <length-username> un numero de dos bytes big endian

- Crear partida

    0x02 

- Unirse partida

    0x03 <length-match> <match-id>

    siendo <length-match> un numero de dos bytes big endian

LOBBY DEBERIA ELEGIR SKINS DE AMBOS LADOS
LOBBY DEBERIA TENER BOTON LISTO
LOBBY DEBERIA TENER ELEGIR MAPA
LOBBY DEBERIA DETERMINAR CUANTOS JUGADORES VAN A SER EN LA PARTIDA

- Comprar arma

    0x04 <weapon-code>

    siendo <weapon-code> un byte 

- Comprar balas

    0x05 <type-weapon> <count>

    siendo <type-weapon> un byte 

    0x01: arma primaria
    0x02: arma secundaria

    <count>: un numero big endian
- Rotar
- Moverse


- Disparar
- Apuntar?
- Cambiar arma
- Plantar la bomba
- Defusear la bomba

#

| Arma   | Código de arma |
|--------|----------------|
| none   | 0x00           |
| glock  | 0x01           |
| ak-47  | 0x02           |
| m3     | 0x03           |
| awp    | 0x04           |

## Server

Los mensajes que envia el server son

- Creaste exitosamente tu nombre de usuario
    0x01 0x01
- Creaste no existosamente tu nombre de usuario
    0x01 0x00
- Creaste exitosamente una partida
    0x02 0x01 
- No creaste exitosamente una partida
    0x02 0x00
- Te uniste exitosamente a una partida
    0x03 0x01
- No te uniste exitosamente a una partida
    0x03 0x00
- Envio equipamiento
    0x04 <money> <knife> <primary-weapon-code> <primary-weapon-bullets> <secondary-weapon-code> <secondary-weapon-bullets>

    - <money>: numero dos bytes big endian
    - <knife>: 0x01 si lo tiene equipado, 0x00 si no (nunca debería pasar)
    - <primary-weapon-code>: un byte
    - <primary-weapon-bullets>: dos bytes big endian
    - <secondary-weapon-code>: un byte
    - <secondary-weapon-bullets>: dos bytes big endian

- Arranca la fase de compra?
- Arranca la ronda en sí 

[Entiendo que con lo de <phase> ya se maneja ¿]

- Cambio de lado?

[SE MANEJA INTERNAMENTE¿]

- Snapshot de la ronda en sí

<phase>: 

- 0x00 buy_phase
- 0x01 round_phase

<round>: 

- 1 byte con el numero de ronda (10 maximo)

<bomb>:

- 0x00 not_planted
- 0x01 planted
- 0x02 explode

<timer>: 1 byte con los segundos, dsp formateamos del lado del client

1min40s de ronda
40s desde q se planta la bomba para explotar

(capaz el explode en <bomb> no hace falta, con ver el timer deberiamos hacer la animación y ya)

<cod-jugadores>: 0x10

<cant-jugadores>: 1 byte

<jugador>:

- username

- pos_x
- pos_y
- dir_x
- dir_y
- pos_cros_x
- pos_cros_y

asumo que 1 byte cada uno, dir_x dir_y es adonde miras, pos_x, pos_y la ubicacion del player, pos_cros_x, pos_cros_y donde está clavada la mira (el puntero del mouse basicamente)

- money
- p-weapon
- p-ammo
- s-weapon
- s-ammo

idem tp1

- bomb

    - 0x00 false
    - 0x01 true

- shooting: 

    - 0x00: false
    - 0x01: true

- w-equipped: 

    - 0x00 knife
    - 0x01 primary
    - 0x02 secondary
    - 0x03 bomb

- health: 1 byte 

<cod-balas-disparadas>: 0x20

<cant-balas-disparadas>: 1 byte asumo

- id bala (creo que son imagenes distintas si disparaste de una primary q de una secondary)
- pos_x
- pos_y
- dir_x
- dir_y