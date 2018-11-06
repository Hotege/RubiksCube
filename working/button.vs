
attribute vec2 positionInput;
attribute vec2 texcoordInput;
varying vec2 texcoordOutput;

void main()
{
	texcoordOutput = texcoordInput;
	gl_Position = vec4(positionInput, 1.0, 1.0);
}