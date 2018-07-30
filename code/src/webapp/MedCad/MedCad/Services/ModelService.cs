using MedCad.Models;
using System;
using System.Linq;

namespace MedCad.Services
{
    public class ModelService : IModelService
    {
        public Model saveModel(Model model)
        {
            using (var context = new ModelContext())
            {
                context.Database.EnsureCreated();

                Model modelInDb;

                try
                {
                    modelInDb = context.Models.Where(_model => _model.MetaData.Name == model.MetaData.Name).First();
                }
                catch (Exception)
                {
                    modelInDb = null;
                }

                if (modelInDb == null)
                {
                    modelInDb = new Model();

                    context.Add(modelInDb);

                    Geometry geometry = new Geometry();
                    MetaData metaData = new MetaData();
                    User user = new User();

                    context.Geometries.Add(geometry);
                    context.MetaDatas.Add(metaData);
                    context.Users.Add(user);

                    geometry.CreatedAt = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
                    geometry.Version = 0;
                    geometry.JsonMeshRepresentation = model.Geometry.JsonMeshRepresentation;
                    geometry.ModelId = modelInDb.ModelId;

                    metaData.CreatedAt = geometry.CreatedAt;
                    metaData.LastVersion = 0;
                    metaData.ModifiedAt = metaData.CreatedAt;
                    metaData.Name = model.MetaData.Name;
                    metaData.TriangleCount = 228;
                    metaData.ModelId = modelInDb.ModelId;

                    user.Email = model.User.Email;
                    user.RegisteredAt = "this functionality is not ready yet";
                    user.ModelId = modelInDb.ModelId;

                    context.SaveChanges();

                    return modelInDb;
                }

                modelInDb.MetaData.ModifiedAt = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
                modelInDb.MetaData.LastVersion = model.Geometry.Version + 1;

                modelInDb.Geometry.Version = modelInDb.MetaData.LastVersion;
                modelInDb.Geometry.CreatedAt = modelInDb.MetaData.ModifiedAt;
                modelInDb.Geometry.JsonMeshRepresentation = model.Geometry.JsonMeshRepresentation;

                modelInDb.User.Email = model.User.Email;


                context.Add(modelInDb);

                context.SaveChanges();

                return modelInDb;
            }
        }

        public Model[] getAllModels()
        {
            var context = new ModelContext();

            return context.Models.ToArray();
        }

        public Model getModel(string fileName)
        {
            var context = new ModelContext();

            return context.Models.Where(model => model.MetaData.Name == fileName).First();
        }
    }
}
