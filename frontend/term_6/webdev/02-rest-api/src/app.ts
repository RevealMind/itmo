import express, { Request, Response } from 'express';
import { FindOptions, Op } from 'sequelize';

import Location from './db/module/Location';

const app = express();

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

/* [TODO] Код вашего приложения */

function get(req: Request, res: Response): void {
  const sortBy = req.body.order || 'createdAt';
  const content = req.body.description;
  const limit = req.body.limit || 100;
  const offset = req.body.limit || 0;

  const options: FindOptions = { limit, offset };

  if (sortBy === 'createdAt' || sortBy === 'name') {
    options.order = [sortBy];
  } else {
    res.status(400);

    return;
  }

  if (content) {
    options.where = { description: { [Op.substring]: content } };
  }

  Location.findAll(options).then(locations => res.status(200).send(locations));
}

function insert(req: Request, res: Response): void {
  const place = {
    name: req.body.name,
    description: req.body.description,
    country: req.body.country,
    city: req.body.city
  };

  Location.create(place).then(() => {
    res.sendStatus(204);
  });
}

function deleteAll(req: Request, res: Response): void {
  Location.destroy({
    truncate: true
  }).then(() => {
    res.sendStatus(204);
  });
}

function getById(req: Request, res: Response): void {
  const id = req.params.id;

  Location.findByPk(id)
    .then(location => {
      if (location) {
        res.send(location);
      } else {
        res.sendStatus(404);
      }
    })
    .catch(() => res.sendStatus(404));
}

function update(req: Request, res: Response): void {
  const id = req.params.id;
  const options = { where: { id } };

  const { updateBy, content } = req.body.update;

  if (
    (updateBy !== 'visited' && updateBy !== 'description') ||
    (updateBy === 'visited' && content !== true && content !== false)
  ) {
    res.sendStatus(404);

    return;
  }

  Location.update({ [updateBy]: content }, options).then(() => res.sendStatus(204));
}

function deleteById(req: Request, res: Response): void {
  const id = req.params.id;
  const options = { where: { id } };

  Location.destroy(options).then(() => res.sendStatus(204));
}

app
  .route('/locations')
  .get(get)
  .post(insert)
  .delete(deleteAll);

app
  .route('/locations/:id')
  .get(getById)
  .patch(update)
  .delete(deleteById);

export default app;
