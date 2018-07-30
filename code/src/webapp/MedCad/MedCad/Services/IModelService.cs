using MedCad.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MedCad.Services
{
    public interface IModelService
    {
        Model saveModel(Model model);
        Model[] getAllModels();
        Model getModel(string fileName);
    }
}
