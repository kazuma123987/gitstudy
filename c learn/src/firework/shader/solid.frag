#version 450
layout(location = 0) in vec2 fragPosition;
layout(location = 1) in vec4 fragColor;
layout(location = 0) out vec4 outFragColor;

void main()
{
    float dist = length(fragPosition);
    if (dist > 1.0)
        discard;
    outFragColor = fragColor;
}