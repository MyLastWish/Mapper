#version 330 core
out vec4 FragmentColor;

uniform vec4 colorVector;
void main()
{
	FragmentColor = colorVector;
}