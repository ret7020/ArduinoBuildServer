# Arguments
# fqbn - Board full name arduino:avr:mega:cpu=atmega2560
# workspace - workspace path

build:
	arduino-cli compile --fqbn $(fqbn) $(workspace)/main --build-path $(workspace)/build
