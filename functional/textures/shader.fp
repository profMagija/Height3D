#version 120

varying vec2 st;
uniform sampler2D image;

void main()
{
  gl_FragColor = texture2D(image, st);
}

