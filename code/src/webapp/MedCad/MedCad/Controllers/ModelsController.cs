using Microsoft.AspNetCore.Mvc;
using MedCad.Models;
using MedCad.Services;
using Newtonsoft.Json;

namespace MedCad.Controllers
{
    [Route("api/[controller]")]
    public class ModelsController : Controller
    {
        public ModelsController(IModelService modelService)
        {
            this.modelService = modelService;
        }

        public IModelService modelService { get; set; }

        [HttpPost]
        public IActionResult saveModel([FromBody]Model model)
        {
            model = modelService.saveModel(model);
            return new ObjectResult(JsonConvert.SerializeObject(model));
        }

        [HttpGet]
        public IActionResult listModels()
        {
            Model[] models = modelService.getAllModels();
            return new ObjectResult(JsonConvert.SerializeObject(models));
        }

        [HttpGet("{name}")]
        public IActionResult getModel(string name)
        {
            Model model = modelService.getModel(name);
            return new ObjectResult(model);
        }
    }

    public class ModelRequest
    {

    }

    public class ModelResponse
    {
    }
}
