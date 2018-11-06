
attribute vec4 positionInput;
varying vec4 positionOutput;
attribute vec4 colorInput;
varying vec4 colorOutput;
attribute vec4 centerInput;
varying vec4 centerOutput;
uniform mat4 mvp;

void main()
{
	gl_Position = mvp * positionInput;
	positionOutput = positionInput;
	colorOutput = colorInput;
	centerOutput = centerInput;
}