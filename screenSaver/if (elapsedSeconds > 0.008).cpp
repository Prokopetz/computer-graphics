if (elapsedSeconds > 0.008)
{
  previousSeconds = currentSeconds;
  float nX;
  float nY;
  bool collision = false;

  if (lastPositionX + 0.5f > 1.0f) // right
  {
    nX = -1.0f;
    nY = 0.0f;
    collision = true;
  }
  else if (lastPositionY + 0.5f > 1.0f) // top
  {
    nX = 0.0f;
    nY = -1.0f;
    collision = true;
  }
  else if (lastPositionX - 0.5f < -1.0f) // left
  {
    nX = 1.0f;
    nY = 0.0f;
    collision = true;
  }
  else if (lastPositionY - 0.5f < -1.0f) // bottom
  {
    nX = 0.0f;
    nY = 1.0f;
    collision = true;
  }

  if (collision)
  {
    float r2X = -speedX;
    float r2Y = -speedY;
    float a = (nX * r2X + nY * r2Y);
    float routX = 2 * nX * a - r2X;
    float routY = 2 * nY * a - r2Y;
    speedX = routX;
    speedY = routY;
  }

  matrix[12] = elapsedSeconds * speedX + lastPositionX;
  matrix[13] = elapsedSeconds * speedY + lastPositionY;
  lastPositionX = matrix[12];
  lastPositionY = matrix[13];
}