/* eslint-disable @typescript-eslint/no-explicit-any */
import supertest from 'supertest';

import app from '../src/app';
import db from '../src/db';

const request = supertest(app);

const cleanDb = async () => {
  const tableNames = Object.keys(db.sequelize.models);
  await db.sequelize.query(
    `TRUNCATE ${tableNames.map(name => `"${name}"`).join(', ')} RESTART IDENTITY CASCADE;`
  );
};

describe('API', () => {
  beforeAll(async () => {
    // Здесь создаются все таблицы по моделям
    await db.sequelize.sync({ force: true });
  });

  beforeEach(async () => {
    await cleanDb();
  });

  it('Должно вернуть список мест', async () => {
    const res = await request.get('/locations');

    expect(res.status).toBe(200);
    expect(res.body).toBeInstanceOf(Array);
  });

  it('Должно вернуть список мест отсортированных по имени', async () => {
    await request.post('/locations').send({
      name: 'Эрмитаж',
      description:
        'Музей изобразительного и декоративно-прикладного искусства, расположенный в городе Санкт-Петербург.'
    });

    await request.post('/locations').send({
      name: 'Летний сад',
      description:
        'Парковый ансамбль, памятник садово-паркового искусства первой трети XVIII века в Центральном районе Санкт-Петербурга.'
    });

    const res = await request.get('/locations').send({
      order: 'name'
    });

    const expectedFirst = {
      name: 'Летний сад',
      description:
        'Парковый ансамбль, памятник садово-паркового искусства первой трети XVIII века в Центральном районе Санкт-Петербурга.',
      visited: false
    };

    const expectedSecond = {
      name: 'Эрмитаж',
      description:
        'Музей изобразительного и декоративно-прикладного искусства, расположенный в городе Санкт-Петербург.',
      visited: false
    };

    expect(res.status).toBe(200);
    expect(res.body[0]).toMatchObject(expectedFirst);
    expect(res.body[1]).toMatchObject(expectedSecond);
  });

  it('Должно вернуть список мест отсортированных по времени', async () => {
    await request.post('/locations').send({
      name: 'Эрмитаж',
      description:
        'Музей изобразительного и декоративно-прикладного искусства, расположенный в городе Санкт-Петербург.'
    });

    await request.post('/locations').send({
      name: 'Летний сад',
      description:
        'Парковый ансамбль, памятник садово-паркового искусства первой трети XVIII века в Центральном районе Санкт-Петербурга.'
    });

    const res = await request.get('/locations').send({
      order: 'createdAt'
    });

    const expectedFirst = {
      name: 'Эрмитаж',
      description:
        'Музей изобразительного и декоративно-прикладного искусства, расположенный в городе Санкт-Петербург.',
      visited: false
    };

    const expectedSecond = {
      name: 'Летний сад',
      description:
        'Парковый ансамбль, памятник садово-паркового искусства первой трети XVIII века в Центральном районе Санкт-Петербурга.',
      visited: false
    };

    expect(res.status).toBe(200);
    expect(res.body[0]).toMatchObject(expectedFirst);
    expect(res.body[1]).toMatchObject(expectedSecond);
  });

  it('Должно вернуть список мест постранично', async () => {
    for (let i = 0; i < 9; i++) {
      await request.post('/locations').send({
        name: 'Эрмитаж',
        description:
          'Музей изобразительного и декоративно-прикладного искусства, расположенный в городе Санкт-Петербург.'
      });
    }

    const res = await request.get('/locations').send({
      limit: 4
    });

    expect(res.status).toBe(200);
    expect(res.body).toHaveLength(4);
  });

  it('Должно вернуть список мест по переданному описанию', async () => {
    const location = {
      name: 'Эрмитаж',
      description:
        'Музей изобразительного и декоративно-прикладного искусства, расположенный в городе Санкт-Петербург.'
    };

    await request.post('/locations').send(location);

    const res = await request.get('/locations').send({
      description: 'Музей изобразительного и декоративно-прикладного искусства'
    });

    expect(res.status).toBe(200);
    expect(res.body[0]).toMatchObject(location);
  });

  it('Должно создать место', async () => {
    const resPost = await request.post('/locations').send({
      name: 'test name',
      description: 'test description'
    });

    const resGet = await request.get('/locations');
    const expectedPartResponse = {
      name: 'test name',
      description: 'test description',
      visited: false
    };

    expect(resPost.status).toBe(204);
    expect(resGet.body[0]).toMatchObject(expectedPartResponse);
  });

  it('Должно вернуть место по id', async () => {
    await request.post('/locations').send({
      name: 'test name by id',
      description: 'test description by id'
    });

    const resGet = await request.get('/locations/1');
    const expectedPartResponse = {
      name: 'test name by id',
      description: 'test description by id',
      visited: false
    };

    expect(resGet.status).toBe(200);
    expect(resGet.body).toMatchObject(expectedPartResponse);
  });

  it('Должно редактировать описание места', async () => {
    await request.post('/locations').send({
      name: 'Эрмитаж',
      description: 'Ничего про него не знаю.'
    });

    const resPatch = await request.patch('/locations/1').send({
      update: {
        updateBy: 'description',
        content:
          'Музей изобразительного и декоративно-прикладного искусства, расположенный в городе Санкт-Петербург.'
      }
    });

    const resGet = await request.get('/locations/1');

    const expectedPartResponse = {
      name: 'Эрмитаж',
      description:
        'Музей изобразительного и декоративно-прикладного искусства, расположенный в городе Санкт-Петербург.',
      visited: false
    };

    expect(resPatch.status).toBe(204);
    expect(resGet.body).toMatchObject(expectedPartResponse);
  });

  it('Должно редактировать информацию о посещении места', async () => {
    await request.post('/locations').send({
      name: 'Эрмитаж',
      description:
        'Музей изобразительного и декоративно-прикладного искусства, расположенный в городе Санкт-Петербург.',
      visited: true
    });

    const resPatch = await request.patch('/locations/1').send({
      update: {
        updateBy: 'visited',
        content: false
      }
    });

    const resGet = await request.get('/locations/1');

    const expectedPartResponse = {
      name: 'Эрмитаж',
      description:
        'Музей изобразительного и декоративно-прикладного искусства, расположенный в городе Санкт-Петербург.',
      visited: false
    };

    expect(resPatch.status).toBe(204);
    expect(resGet.body).toMatchObject(expectedPartResponse);
  });

  it('Должно удалить место по id', async () => {
    await request.post('/locations').send({
      name: 'test name by id',
      description: 'test description by id'
    });
    const resDelete = await request.delete('/locations/1');
    const resGetAfter = await request.get('/locations/1');

    expect(resDelete.status).toBe(204);
    expect(resGetAfter.status).toBe(404);
  });
});
