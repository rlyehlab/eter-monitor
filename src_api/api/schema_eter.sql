--
-- PostgreSQL database dump
--

-- Dumped from database version 9.6.7
-- Dumped by pg_dump version 9.6.7

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: device; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE device (
    id integer NOT NULL,
    date_created timestamp without time zone,
    state boolean,
    geolocation character varying(128),
    user_id integer
);


ALTER TABLE device OWNER TO admin;

--
-- Name: device_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE device_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE device_id_seq OWNER TO admin;

--
-- Name: device_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE device_id_seq OWNED BY device.id;


--
-- Name: measure; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE measure (
    id integer NOT NULL,
    date_created timestamp without time zone,
    sensor_id integer,
    device_id integer,
    value character varying(6) NOT NULL
);


ALTER TABLE measure OWNER TO admin;

--
-- Name: measure_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE measure_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE measure_id_seq OWNER TO admin;

--
-- Name: measure_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE measure_id_seq OWNED BY measure.id;


--
-- Name: sensor; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE sensor (
    id integer NOT NULL,
    date_created timestamp without time zone,
    name character varying(30) NOT NULL,
    variable character varying(30) NOT NULL,
    description character varying(128)
);


ALTER TABLE sensor OWNER TO admin;

--
-- Name: sensor_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE sensor_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE sensor_id_seq OWNER TO admin;

--
-- Name: sensor_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE sensor_id_seq OWNED BY sensor.id;


--
-- Name: user; Type: TABLE; Schema: public; Owner: admin
--

CREATE TABLE "user" (
    id integer NOT NULL,
    date_created timestamp without time zone,
    name character varying(128),
    email character varying(128) NOT NULL,
    password character varying(128)
);


ALTER TABLE "user" OWNER TO admin;

--
-- Name: user_id_seq; Type: SEQUENCE; Schema: public; Owner: admin
--

CREATE SEQUENCE user_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE user_id_seq OWNER TO admin;

--
-- Name: user_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: admin
--

ALTER SEQUENCE user_id_seq OWNED BY "user".id;


--
-- Name: device id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY device ALTER COLUMN id SET DEFAULT nextval('device_id_seq'::regclass);


--
-- Name: measure id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY measure ALTER COLUMN id SET DEFAULT nextval('measure_id_seq'::regclass);


--
-- Name: sensor id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY sensor ALTER COLUMN id SET DEFAULT nextval('sensor_id_seq'::regclass);


--
-- Name: user id; Type: DEFAULT; Schema: public; Owner: admin
--

ALTER TABLE ONLY "user" ALTER COLUMN id SET DEFAULT nextval('user_id_seq'::regclass);


--
-- Name: device device_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY device
    ADD CONSTRAINT device_pkey PRIMARY KEY (id);


--
-- Name: measure measure_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY measure
    ADD CONSTRAINT measure_pkey PRIMARY KEY (id);


--
-- Name: sensor sensor_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY sensor
    ADD CONSTRAINT sensor_pkey PRIMARY KEY (id);


--
-- Name: user user_pkey; Type: CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY "user"
    ADD CONSTRAINT user_pkey PRIMARY KEY (id);


--
-- Name: device device_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY device
    ADD CONSTRAINT device_user_id_fkey FOREIGN KEY (user_id) REFERENCES "user"(id);


--
-- Name: measure measure_device_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY measure
    ADD CONSTRAINT measure_device_id_fkey FOREIGN KEY (device_id) REFERENCES device(id);


--
-- Name: measure measure_sensor_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: admin
--

ALTER TABLE ONLY measure
    ADD CONSTRAINT measure_sensor_id_fkey FOREIGN KEY (sensor_id) REFERENCES sensor(id);


--
-- PostgreSQL database dump complete
--

