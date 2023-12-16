--
-- PostgreSQL database cluster dump
--

-- Started on 2023-12-16 09:47:20 CET

SET default_transaction_read_only = off;

SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;

--
-- Roles
--

CREATE ROLE postgres;
ALTER ROLE postgres WITH SUPERUSER INHERIT CREATEROLE CREATEDB LOGIN REPLICATION BYPASSRLS PASSWORD 'SCRAM-SHA-256$4096:csH0hKONe2h14VNQc4gXSA==$4BjhJmjczcmjqPuXb3nvBlPd/kkc5i15iQLuEEsWHcc=:mGmEgGQKHRppWTmkQ8kkUPCIyCjBlz1ZMZeBNJAd+h4=';

--
-- User Configurations
--








--
-- Databases
--

--
-- Database "template1" dump
--

\connect template1

--
-- PostgreSQL database dump
--

-- Dumped from database version 15.3
-- Dumped by pg_dump version 16.1 (Ubuntu 16.1-1.pgdg22.04+1)

-- Started on 2023-12-16 09:47:20 CET

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

-- Completed on 2023-12-16 09:47:23 CET

--
-- PostgreSQL database dump complete
--

--
-- Database "postgres" dump
--

\connect postgres

--
-- PostgreSQL database dump
--

-- Dumped from database version 15.3
-- Dumped by pg_dump version 16.1 (Ubuntu 16.1-1.pgdg22.04+1)

-- Started on 2023-12-16 09:47:23 CET

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 214 (class 1259 OID 16386)
-- Name: setup_esp32; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.setup_esp32 (
    name text NOT NULL,
    value double precision NOT NULL
);


ALTER TABLE public.setup_esp32 OWNER TO postgres;

--
-- TOC entry 3339 (class 0 OID 16386)
-- Dependencies: 214
-- Data for Name: setup_esp32; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.setup_esp32 (name, value) FROM stdin;
motor_right_direction	1
motion_pid_angle_direction	0
motion_pid_angle_kp	1
motion_pid_angle_kd	0.2
motion_pid_angle_ki	0.2
motion_pid_angle_mv_max	100
motion_pid_angle_mv_min	-100
motion_pid_pitch_ki	25
motion_pid_pitch_mv_max	100
motion_pid_position_kp	5
motion_pid_position_mv_max	10
motion_pid_position_mv_min	-8
encoder_left_direction	0
motor_right_offset	3
encoder_right_direction	0
imu_offset_pitch	-4
imu_invert_pitch	0
motor_left_direction	0
imu_invert_roll	0
imu_invert_yaw	0
motion_pid_pitch_kp	5
motion_pid_position_kd	8
motion_pid_position_direction	0
odometry_distance_wheels	0.231
odometry_wheel_radio	0.035
motion_pid_pitch_direction	1
motion_pid_pitch_mv_min	-100
motion_pid_pitch_kd	0.25
motion_pid_position_ki	1.5
motor_left_offset	3
motion_falldown_offset	45
\.


--
-- TOC entry 3196 (class 2606 OID 16392)
-- Name: setup_esp32 setup_esp32_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.setup_esp32
    ADD CONSTRAINT setup_esp32_pkey PRIMARY KEY (name);


-- Completed on 2023-12-16 09:47:24 CET

--
-- PostgreSQL database dump complete
--

-- Completed on 2023-12-16 09:47:24 CET

--
-- PostgreSQL database cluster dump complete
--

