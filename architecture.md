# Protocol

## Client

Puede enviar todos estos requests:

- Crear nombre de usuario

    0x01 _length-username_ _username_
    
    siendo _length-username_ un numero de dos bytes big endian

- Crear partida

    0x02 _amount-of-players_

- Unirse partida

    0x03 _length-match_ _match-id_

    siendo _length-match_ un numero de dos bytes big endian

UNA VEZ UNIDO:

- Elegir skins

    0x04 _skin-id-tt_: 1 byte _skin-id-ct_: 1 byte

    // podria hacer algo similar a lo del tp2 del OR para achicar esto un poco

- Elegir mapa

    0x05 _map-id_: 1 byte

- Comprar arma

    0x06 _weapon-code_

    siendo _weapon-code_ un byte 

- Comprar balas

    0x07 _type-weapon_ _count_

    siendo _type-weapon_ un byte 

    0x01: arma primaria

    0x02: arma secundaria

    _count_: un numero big endian

- Apuntar (y rotar):

    0x08 _position-crosshair_

- Moverse

    0x09 _direction_:

    - 0x01: arriba
    - 0x02: izquierda
    - 0x03: abajo
    - 0x04: derecha

- Disparar

    0x10 (con la dirección ya debería saber adonde va)

- Cambiar arma

    0x11 _weapon-id_:

    0x00 knife
    
    0x01 primary

    0x02 secondary

    0x03 bomb

- Plantar la bomba

    0x12 
    
    // ACA CAPAZ DEBERIA SER IGUAL Q SHOOTEAR CUANDO TENES SELECCIONADA LA BOMBA. 

- Defusear la bomba

    0x13 // ACÁ ESTÁ BIEN Q SEA OTRA, EN EL CS2 Y CSGO USAS E PARA DEFUSEAR

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
    0x04 _money_ _knife_ _primary-weapon-code_ _primary-weapon-bullets_ _secondary-weapon-code_ _secondary-weapon-bullets_

    - _money_: numero dos bytes big endian
    - _knife_: 0x01 si lo tiene equipado, 0x00 si no (nunca debería pasar)
    - _primary-weapon-code_: un byte
    - _primary-weapon-bullets_: dos bytes big endian
    - _secondary-weapon-code_: un byte
    - _secondary-weapon-bullets_: dos bytes big endian

_phase_: 

- 0x00 buy_phase
- 0x01 round_phase

_round_: 

- 1 byte con el numero de ronda (10 maximo)

_bomb_:

- 0x00 not_planted
- 0x01 planted
- 0x02 explode

_timer_: 1 byte con los segundos, dsp formateamos del lado del client

1min40s de ronda
40s desde q se planta la bomba para explotar

(capaz el explode en _bomb_ no hace falta, con ver el timer deberiamos hacer la animación y ya)

_cod-jugadores_: 0x10

_cant-jugadores_: 1 byte

_jugador_:

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

_cod-balas-disparadas_: 0x20

_cant-balas-disparadas_: 1 byte asumo

- id bala (creo que son imagenes distintas si disparaste de una primary q de una secondary)
- pos_x
- pos_y
- dir_x
- dir_y