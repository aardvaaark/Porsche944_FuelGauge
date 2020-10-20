# Porsche Spec944 Standalone Fuel Gauge
Stand alone fuel gauge setup based on Arduino architecture. Scaling specific to the 1985.5+ Porsche 944 fuel level sending unit.

## Requirements

1. 12v power from the car must be converted to ~5v to power ardiuno and display
1. Consume signal from fuel level sending unit
    - May be based on voltage drop or maybe be resistance based. Either circuit will read the output of the level sensing potentiometer (TBD)
1. Parse sensor output
    - Determine min and max for level sensor
    - Map values into 0-100% values
1. Display mapped values as either percentage or bar chart
1. Smooth display reading (to account for fuel slosh in the tank)

## Hardware

1. Board
    - PT#
1. Power invertor
    - PT#
1. Display
    - PT#
1. Mount/Case
    - PT#

## Circuit

Design tool: https://fritzing.org/
