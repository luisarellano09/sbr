PGDMP                      {           sbr    15.3     16.0 (Ubuntu 16.0-1.pgdg22.04+1)                0    0    ENCODING    ENCODING        SET client_encoding = 'UTF8';
                      false                       0    0 
   STDSTRINGS 
   STDSTRINGS     (   SET standard_conforming_strings = 'on';
                      false                       0    0 
   SEARCHPATH 
   SEARCHPATH     8   SELECT pg_catalog.set_config('search_path', '', false);
                      false                       1262    16400    sbr    DATABASE     n   CREATE DATABASE sbr WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE_PROVIDER = libc LOCALE = 'en_US.utf8';
    DROP DATABASE sbr;
                sbr    false            �            1259    32776    setup_esp32    TABLE     a   CREATE TABLE public.setup_esp32 (
    name text NOT NULL,
    value double precision NOT NULL
);
    DROP TABLE public.setup_esp32;
       public         heap    sbr    false                      0    32776    setup_esp32 
   TABLE DATA           2   COPY public.setup_esp32 (name, value) FROM stdin;
    public          sbr    false    214   6       |           2606    32782    setup_esp32 setup_esp32_pkey 
   CONSTRAINT     \   ALTER TABLE ONLY public.setup_esp32
    ADD CONSTRAINT setup_esp32_pkey PRIMARY KEY (name);
 F   ALTER TABLE ONLY public.setup_esp32 DROP CONSTRAINT setup_esp32_pkey;
       public            sbr    false    214               �   x�u�Ѯ� ���]��<K�0'!D�l� �mo?�L���������LI'�6Y[LPe� 
�i8�V�pu��jo�K�Y��'FG^����!
�TqX���j�Bo�鼕�:�Z/c{gE����]:4�*����:�G:�@u�B���GI���?��Ϩa� M����"2�s���ܿ3�v���Goȅ�.Ȓ�����f*������e������H=R%����~�V��(�|,i     