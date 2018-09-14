CREATE TABLE "messages" (
    id SERIAL PRIMARY KEY,
    created_at timestamp DEFAULT current_timestamp,
    hash CHAR(16) NOT NULL UNIQUE,
    topic character varying(128) NOT NULL,
    message text NOT NULL
);

CREATE TABLE "measurements" (
  id SERIAL PRIMARY KEY,
  created_at timestamp DEFAULT current_timestamp,
  hash CHAR(16) NOT NULL UNIQUE,
  mac VARCHAR(64) NOT NULL,
  type VARCHAR(64) NOT NULL,
  data jsonb
);
