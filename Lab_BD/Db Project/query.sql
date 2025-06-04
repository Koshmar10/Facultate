-- Interogarea 1: Listează numele școlilor care au cel puțin o grupă ce predă un curs cu limbajul 'Python'.
--toate scolile care prededau python
SELECT S.NUME_SCOALA
FROM SCOLI S
JOIN GRUPE G ON G.ID_SCOALA = S.ID_SCOALA
WHERE G.CURS IN (
    SELECT C.NUME_CURS
    FROM CURSURI C
    WHERE C.LIMBAJ_CURS = 'Python'
    );
-- Interogarea 2: Afișează profesorii care au mai mulți elevi decât media tuturor profesorilor,
-- împreună cu o clasificare pe activitate.

WITH ELEVI_PER_PROFESOR AS (
    SELECT
        P.NUME_PROFESOR,
        P.ID_PROFESOR,
           COUNT(E.ID_ELEV) AS NUMAR_ELEVI,
           P.EMAIL_PROFESOR
    FROM PROFESORI P
    JOIN GRUPE G ON P.ID_PROFESOR = G.ID_PROFESOR
    JOIN ELEVI E ON G.ID_GRUPA = E.ID_GRUPA
    GROUP BY P.ID_PROFESOR, P.NUME_PROFESOR, P.EMAIL_PROFESOR
),
MEDIA_ELEVI AS (
    SELECT AVG(NUMAR_ELEVI) AS MEDIA FROM ELEVI_PER_PROFESOR
)
SELECT
    EPE.NUME_PROFESOR,
    NVL(EPE.EMAIL_PROFESOR, 'email necunoscut'),
    EPE.NUMAR_ELEVI,
    CASE
        WHEN EPE.NUMAR_ELEVI > 4 THEN 'Foarte activ'
        WHEN EPE.NUMAR_ELEVI BETWEEN 2 AND 4 THEN 'Activ'
        ELSE 'Putin activ'
    END AS CATEGORIE_PROFESOR

FROM ELEVI_PER_PROFESOR EPE, MEDIA_ELEVI M
WHERE EPE.NUMAR_ELEVI >= M.MEDIA;



-- Interogarea 3: Calculează procentul elevilor din fiecare școală care participă la grupe de nivel 'Avansati'.
SELECT S.NUME_SCOALA,
       ROUND (
        COUNT(CASE WHEN G.CATEGORIE = 'Avansati' THEN 1 END) * 100.0 / COUNT(E.ID_ELEV)
           ,2
       )
           AS PROCENT_ELEVI_AVANSATI
FROM SCOLI S
JOIN ELEVI E ON S.ID_SCOALA = E.ID_SCOALA
JOIN GRUPE G ON E.ID_GRUPA = G.ID_GRUPA
GROUP BY S.NUME_SCOALA
HAVING COUNT(CASE WHEN G.CATEGORIE = 'Avansati' THEN 1 END) * 100.0 / COUNT(E.ID_ELEV)> 0
ORDER BY PROCENT_ELEVI_AVANSATI DESC;

-- Interogarea 4: Calculează data la care se încheie fiecare grupă, adunând durata cursului la data de început.
SELECT
    g.ID_GRUPA,
    g.CURS,
    TO_CHAR(g.DATA_INCEPUT, 'DD-MM-YYYY') AS DATA_INCEPUT,
    g.ZI_GRUPA,
    TRUNC( (SYSDATE - (g.DATA_INCEPUT +
           MOD(
             DECODE(g.ZI_GRUPA,
               'Luni', 0,
               'Marti', 1,
               'Miercuri', 2,
               'Joi', 3,
               'Vineri', 4,
               0
             ) - TO_CHAR(g.DATA_INCEPUT, 'D')
           , 7)
         )
        ) / 7 ) + 1 AS SAPTAMANA_CURENTA
FROM GRUPE g
WHERE SYSDATE >= g.DATA_INCEPUT;

--Interogarea 5: afiseaza numarul de feete si de baieti din fiecare scoala
SELECT
    s.NUME_SCOALA,
    COUNT(CASE WHEN SUBSTR(e.CNP_ELEV, 1, 1) IN ('2', '4', '6') THEN 1 END) AS NR_FETE,
    COUNT(CASE WHEN SUBSTR(e.CNP_ELEV, 1, 1) IN ('1', '3', '5') THEN 1 END) AS NR_BAIETI
FROM ELEVI e
JOIN SCOLI s ON e.ID_SCOALA = s.ID_SCOALA
GROUP BY s.NUME_SCOALA
ORDER BY s.NUME_SCOALA;


--cerinta 13
-- Operatie 1: In momentul in care o grupa isi termina activitatea, fiecare elev al grupei
-- va avea cursul grupei asociat in tabelul Elevi_Cursuri, marcand faptul ca elevii respectivi au completat cursul
INSERT INTO ELEVI_CURSURI (ID_ELEV, NUME_CURS)
SELECT
    E.ID_ELEV,
    G.CURS
FROM
    GRUPE G
    JOIN ELEVI E ON E.ID_GRUPA = G.ID_GRUPA
    JOIN CURSURI C ON G.CURS = C.NUME_CURS
WHERE
    G.DATA_INCEPUT + (7 * C.DURATA_CURS) < SYSDATE
    AND NOT EXISTS (
        SELECT 1
        FROM ELEVI_CURSURI EC
        WHERE EC.ID_ELEV = e.ID_ELEV AND EC.NUME_CURS = G.CURS
    );

--Operatie 2: grupele care si-au terminat activiatea sunt sterse din sistem
DELETE FROM GRUPE
WHERE ID_GRUPA IN (
    SELECT G.ID_GRUPA
    FROM GRUPE G
    JOIN CURSURI C ON G.CURS= C.NUME_CURS
    WHERE G.DATA_INCEPUT + (7 * C.DURATA_CURS) < SYSDATE
);

--Operatie: sincronizeaza nivelul grpelor cu nivelul cursurilor asociate fiecarei grupa
UPDATE GRUPE G
SET CATEGORIE = (
    SELECT C.NIVEL_CURS
    FROM CURSURI C
    WHERE C.NUME_CURS = G.CURS
)
WHERE EXISTS (
    SELECT 1
    FROM CURSURI C
    WHERE C.NUME_CURS = G.CURS
);
